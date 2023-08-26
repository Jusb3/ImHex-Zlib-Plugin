#include <pl.hpp>
#include <hex/api/content_registry.hpp>
#include <zlib.h>

#include <pl/core/token.hpp>
#include <pl/core/log_console.hpp>
#include <pl/core/evaluator.hpp>
#include <pl/patterns/pattern.hpp>

#include <wolv/hash/crc.hpp>
#include <hex/plugin.hpp>

#define CHUNK 16384

/* Zlib inflate for std::vector<u8>. Zlib can autodetect and decompress deflate strems in raw deflate, zlib wrapped and gzip wrapped formats.*/
std::vector<u8> inflate_bytes(std::vector<u8> in)
{
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char out[CHUNK];
    std::vector<u8> result;
    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return result;
    size_t length=in.size();
    /* decompress until end of buffer */
    if(length > 0){
        strm.avail_in = length;
        strm.next_in = &in[0];

        /* run inflate() on input until output buffer not full */
        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret) {
            case Z_NEED_DICT:
            case Z_DATA_ERROR:
            case Z_MEM_ERROR:
                (void)inflateEnd(&strm);
                return result;
            }
            have = CHUNK - strm.avail_out;
            result.insert(result.end(), out, out + have);
        } while (strm.avail_out == 0);
    }
    
    /* clean up and return */
    (void)inflateEnd(&strm);
    return result;
}
IMHEX_PLUGIN_SETUP("Zlib", "Jusb3", "Zlib inflate interface to PL.") {
    using namespace pl::core;
    using FunctionParameterCount = pl::api::FunctionParameterCount;
    pl::api::Namespace nsZlib = { "zlib" };
    /* decompress(bytes) */
    hex::ContentRegistry::PatternLanguage::addFunction(nsZlib, "decompress", FunctionParameterCount::exactly(1), [](Evaluator *ctx, auto params) -> std::optional<Token::Literal> {
        wolv::util::unused(ctx);

        auto pattern = params[0].toPattern();
        std::vector<u8> result = inflate_bytes(pattern->getBytes());
        return std::string(result.begin(), result.end());
    });
}
