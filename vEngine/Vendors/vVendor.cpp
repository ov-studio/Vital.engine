#ifndef _CRT_SECURE_NO_WARNINGS
    #define _CRT_SECURE_NO_WARNINGS
#endif

#define STB_IMAGE_IMPLEMENTATION
#include "Vendors/stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Vendors/stb/stb_image_write.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "Utils/stb_truetype.h"

#define TINYDDSLOADER_IMPLEMENTATION
#include "Vendors/tiny_dds/tinyddsloader.h"

#define BASISU_NO_ITERATOR_DEBUG_LEVEL
#include "Vendors/basis_universal/transcoder/basisu_transcoder.cpp"
#undef _CRT_SECURE_NO_WARNINGS
#include "Vendors/basis_universal/encoder/jpgd.cpp"
#include "Vendors/basis_universal/encoder/lodepng.cpp"
#include "Vendors/basis_universal/encoder/apg_bmp.c"
#include "Vendors/basis_universal/encoder/basisu_astc_decomp.cpp"
#include "Vendors/basis_universal/encoder/basisu_backend.cpp"
#include "Vendors/basis_universal/encoder/basisu_basis_file.cpp"
#include "Vendors/basis_universal/encoder/basisu_bc7enc.cpp"
#include "Vendors/basis_universal/encoder/basisu_comp.cpp"
#include "Vendors/basis_universal/encoder/basisu_enc.cpp"
#include "Vendors/basis_universal/encoder/basisu_etc.cpp"
#include "Vendors/basis_universal/encoder/basisu_frontend.cpp"
#include "Vendors/basis_universal/encoder/basisu_global_selector_palette_helpers.cpp"
#include "Vendors/basis_universal/encoder/basisu_gpu_texture.cpp"
#include "Vendors/basis_universal/encoder/basisu_kernels_sse.cpp"
#include "Vendors/basis_universal/encoder/basisu_pvrtc1_4.cpp"
#include "Vendors/basis_universal/encoder/basisu_resampler.cpp"
#include "Vendors/basis_universal/encoder/basisu_resample_filters.cpp"
#include "Vendors/basis_universal/encoder/basisu_ssim.cpp"
#include "Vendors/basis_universal/encoder/basisu_uastc_enc.cpp"

#undef CLAMP

//#include "Vendors/basis_universal/zstd/zstddeclib.c"
#include "Vendors/basis_universal/zstd/zstd.c"
basist::etc1_global_selector_codebook g_basis_global_codebook(basist::g_global_selector_cb_size, basist::g_global_selector_cb);

