#ifndef _INPUT_SOURCE_HANDLER_H_
#define _INPUT_SOURCE_HANDLER_H_

#include <cstdint>
#include <string>
#include <vector>
#include <complex>
#include <algorithm>

#include <QFile>

#include "utilities.h"

//-----------------------------------------------------------------------------
class data_samples_impl {
public:
    virtual uint64_t get_sample_size() = 0;
    virtual void copy_range(const void* const src, size_t start, size_t length, std::complex<float>* const dest) = 0;
    virtual void set_scale(float fs) = 0;
    virtual ~data_samples_impl() { };

    float full_scale = 2048.0f;

};  // end of class data_samples_impl

//-----------------------------------------------------------------------------
template <typename T>
class data_samples : public data_samples_impl
{

public:
    //-----------------------------------------------------------------------------
    //data_samples() = default;

    //data_samples(float fs) : full_scale(fs) {}

    //-----------------------------------------------------------------------------
    uint64_t sample_size = sizeof(std::complex<T>);
    uint64_t get_sample_size() override { return sample_size; }

    //-----------------------------------------------------------------------------
    void copy_range(const void* const src, size_t start, size_t length, std::complex<float>* const dest) override
    {
        auto s = reinterpret_cast<const std::complex<T>*>(src);
        float k = 1.0f / full_scale;

        std::transform(&s[start], &s[start + length], dest,
            [&k](const std::complex<T>& v) -> std::complex<float> 
            {
                return { (float)(v.real()) * k, (float)(v.imag()) * k };
            }
        );
    }

    //-----------------------------------------------------------------------------
    void set_scale(float fs) override { full_scale = fs; }

    //-----------------------------------------------------------------------------
    //~data_samples() override { };

};  // end of data_samples


//-----------------------------------------------------------------------------
class input_source
{

public:
    input_source() 
    {
        samples = std::make_unique<data_samples<float>>();
    }
    
    //-----------------------------------------------------------------------------
    std::unique_ptr<std::complex<float>> get_samples(int64_t start, int64_t length)
    {

        if (sample_data == nullptr)
            return nullptr;

        if (start < 0 || length < 0)
            return nullptr;

        if (start + length > sample_count)
            return nullptr;

        auto dest = std::make_unique<std::complex<float>>(length);
        samples->copy_range(sample_data, start, length, dest.get());

        return dest;
    }

    //-----------------------------------------------------------------------------
    uint64_t get_sample_count() { return sample_count; }
    
    //-----------------------------------------------------------------------------
    void read_file(std::string filename)
    {
        std::string file_ext = get_file_extension(filename);

        if ((file_ext == "cfile") || (file_ext == "cf32") || (file_ext == "fc32")) {
            samples = std::make_unique<data_samples<float>>();
        }
        else if ((file_ext == "cf64") || (file_ext == "fc64")) {
            samples = std::make_unique<data_samples<double>>();
        }
        else if ((file_ext == "cs32") || (file_ext == "sc32") || (file_ext == "c32")) {
            samples = std::make_unique<data_samples<int32_t>>();
        }
        else if ((file_ext == "cs16") || (file_ext == "sc16") || (file_ext == "c16")) {
            samples = std::make_unique<data_samples<int16_t>>();
        }
        else if ((file_ext == "cs8") || (file_ext == "sc8") || (file_ext == "c8")) {
            samples = std::make_unique<data_samples<int8_t>>();
        }
        else if ((file_ext == "cu8") || (file_ext == "uc8")) {
            samples = std::make_unique<data_samples<int8_t>>();
        }
        //else if (file_ext == "f32") {
        //    samples = std::make_unique<RealF32SampleAdapter>();
        //    _realSignal = true;
        //}
        //else if (file_ext == "f64") {
        //    samples = std::make_unique<RealF64SampleAdapter>();
        //    _realSignal = true;
        //}
        //else if (file_ext == "s16") {
        //    samples = std::make_unique<RealS16SampleAdapter>();
        //    _realSignal = true;
        //}
        //else if (file_ext == "s8") {
        //    samples = std::make_unique<RealS8SampleAdapter>();
        //    _realSignal = true;
        //}
        //else if (file_ext == "u8") {
        //    samples = std::make_unique<RealU8SampleAdapter>();
        //    _realSignal = true;
        //}
        else {
            samples = std::make_unique<data_samples<float>>();
        }

        samples->set_scale(full_scale);

        auto file = std::make_unique<QFile>(QString(filename.c_str()));
        if (!file->open(QFile::ReadOnly)) 
        {
            throw std::runtime_error(file->errorString().toStdString());
        }

        int64_t size = file->size();
        sample_count = size / samples->get_sample_size();

        auto data = file->map(0, size);
        if (data == nullptr)
            throw std::runtime_error("Error mmapping file");

        //cleanup();

        //inputFile = file.release();
        file.release();
        sample_data = data;

        //invalidate();

    }   // end of read_file
    
private:

    float full_scale = 2048.0f;
    
    std::unique_ptr<data_samples_impl> samples;

    uint64_t sample_count = 0;
    uint8_t *sample_data = nullptr;
    
    bool real_signal = false;

};  // end of class input_source

#endif  // _INPUT_SOURCE_HANDLER_H_
