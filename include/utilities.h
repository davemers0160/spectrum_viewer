#ifndef _UTILITIES_H_
#define	_UTILITIES_H_

#include <cstdint>
#include <vector>
#include <string>
#include <complex>
#include <algorithm>


//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>

//-----------------------------------------------------------------------------
//class data_samples_impl {
//public:
//    virtual uint64_t get_sample_size() = 0;
//    virtual void copy_range(const void* const src, size_t start, size_t length, std::complex<float>* const dest) = 0;
//    virtual void set_scale(float fs) = 0;
//    virtual ~data_samples_impl() {};
//
//    float full_scale = 2048.0f;
//
//};

//-----------------------------------------------------------------------------
//template <typename T>
//class data_samples : public data_samples_impl
//{
//
//public:
//    //float full_scale = 2048.0f;
//
//    //-----------------------------------------------------------------------------
//    //data_samples() = default;
//
//    //data_samples(float fs) : full_scale(fs) {}
//
//    //-----------------------------------------------------------------------------
//    uint64_t sample_size = sizeof(std::complex<T>);
//    uint64_t get_sample_size() override { return sample_size; }
//
//    //-----------------------------------------------------------------------------
//    void copy_range(const void* const src, size_t start, size_t length, std::complex<float>* dest) override
//    {
//        auto s = reinterpret_cast<const std::complex<T>*>(src);
//        float k = 1.0f / full_scale;
//
//        std::transform(&s[start], &s[start + length], dest,
//            [&k](const std::complex<T>& v) -> std::complex<float> 
//            {
//                return { (float)(v.real()) * k, (float)(v.imag()) * k };
//            }
//        );
//    }
//
//    //-----------------------------------------------------------------------------
//    void set_scale(float fs) override { full_scale = fs; }
//
//    //-----------------------------------------------------------------------------
//    ~data_samples() override { };
//
//};



//-----------------------------------------------------------------------------
inline std::string get_file_extension(std::string filename)
{
    std::string file_ext;

    // get the extension location
    std::size_t file_ext_loc = filename.rfind('.') + 1;

    if (file_ext_loc > filename.length())
        file_ext = "";
    else
        file_ext = filename.substr(file_ext_loc, (filename.length() - file_ext_loc));

    return file_ext;

}	// end of get_file_parts

//-----------------------------------------------------------------------------
//inline void read_iq_file(std::string filename, float full_scale, std::unique_ptr<data_samples_impl> &samples, uint8_t *iq_data)
//{
//    std::string file_ext = get_file_extension(filename);
//
//	//data.clear();
//
//    if ((file_ext == "cfile") || (file_ext == "cf32") || (file_ext == "fc32")) {
//        samples = std::make_unique<data_samples<float>>();
//    }
//    else if ((file_ext == "cf64") || (file_ext == "fc64")) {
//        samples = std::make_unique<data_samples<double>>();
//    }
//    else if ((file_ext == "cs32") || (file_ext == "sc32") || (file_ext == "c32")) {
//        samples = std::make_unique<data_samples<int32_t>>();
//    }
//    else if ((file_ext == "cs16") || (file_ext == "sc16") || (file_ext == "c16")) {
//        samples = std::make_unique<data_samples<int16_t>>();
//    }
//    else if ((file_ext == "cs8") || (file_ext == "sc8") || (file_ext == "c8")) {
//        samples = std::make_unique<data_samples<int8_t>>();
//    }
//    else if ((file_ext == "cu8") || (file_ext == "uc8")) {
//        samples = std::make_unique<data_samples<int8_t>>();
//    }
//    //else if (file_ext == "f32") {
//    //    samples = std::make_unique<RealF32SampleAdapter>();
//    //    _realSignal = true;
//    //}
//    //else if (file_ext == "f64") {
//    //    samples = std::make_unique<RealF64SampleAdapter>();
//    //    _realSignal = true;
//    //}
//    //else if (file_ext == "s16") {
//    //    samples = std::make_unique<RealS16SampleAdapter>();
//    //    _realSignal = true;
//    //}
//    //else if (file_ext == "s8") {
//    //    samples = std::make_unique<RealS8SampleAdapter>();
//    //    _realSignal = true;
//    //}
//    //else if (file_ext == "u8") {
//    //    samples = std::make_unique<RealU8SampleAdapter>();
//    //    _realSignal = true;
//    //}
//    else {
//        samples = std::make_unique<data_samples<float>>();
//    }
//
//    samples->set_scale(full_scale);
//
//    auto file = std::make_unique<QFile>(QString(filename.c_str()));
//    if (!file->open(QFile::ReadOnly)) 
//    {
//        throw std::runtime_error(file->errorString().toStdString());
//    }
//
//    int64_t size = file->size();
//    auto sample_count = size / samples->get_sample_size();
//
//    auto data = file->map(0, size);
//    if (data == nullptr)
//        throw std::runtime_error("Error mmapping file");
//
//    //cleanup();
//
//    //inputFile = file.release();
//    file.release();
//    iq_data = data;
//
//    //invalidate();
//
//}   // end of read_iq_file

#endif	// _UTILITIES_H_