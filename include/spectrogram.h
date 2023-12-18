#ifndef _SPECTROGRAM_H_
#define _SPECTROGRAM_H_


#include <cstdint>
#include <vector>
#include <complex>

#include <liquid.h>

//-----------------------------------------------------------------------------
// assumes all samples are in the range [-1, 1]
class spectrogram
{

public:

uint64_t sample_rate;
uint32_t fft_size;
uint32_t window_size;
uint32_t overlap;

spectrogram() = default;

spectrogram(uint64_t sr, uint32_t fs, uint32_t ws, uint32_t ov) : sample_rate(sr), fft_size(fs), window_size(ws), overlap(ov) {}

//-----------------------------------------------------------------------------

inline void generate_spectrogram()
{
    
}

//-----------------------------------------------------------------------------
inline void compute_fft()

private:
//float full_scale = 2048.0f;


};

#endif  // _SPECTROGRAM_H_
