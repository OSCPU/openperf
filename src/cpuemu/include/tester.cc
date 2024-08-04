#include <array>
#include <lest.hpp>

#include "uint.h"
#include "sint.h"


UInt<16>  a16u(0xcafe);
UInt<16>  b16u(0xbebe);
UInt<64>  a64u(0xe2bd5b4ff8b30fc8);
UInt<64>  b64u(0x2fc353e33c6938a7);
UInt<80>  a80u("0x987426c1f7cd7d4d693a");
UInt<80>  b80u("0x563a0757a07b7bd27485");
UInt<128> a128u("0xe903646a697fcaa344d2b2aa95e47b5d");
UInt<128> b128u("0x56fa570ecb04adca42405f12bf28b822");

SInt<16>  a16s(0x6dba);
SInt<16>  b16s(0xccb2);
SInt<64>  a64s(0x71088d1c4a5c4a02);
SInt<64>  b64s(0xdefaa415d9062302);
SInt<80>  a80s("0x381c1fe6bca6875922fe");
SInt<80>  b80s("0xefbe8ae0d38ab7f36dda");
SInt<128> a128s("0x6e0939370acc19daec06e9c13db50674");
SInt<128> b128s("0xbeb828fdbac591dba8e38eeb433f563d");


const lest::test spec[] = {
  CASE("uint comparison operators") {
    EXPECT( a16u == a16u );
    EXPECT( a16u != b16u );
    EXPECT( b16u <  a16u );
    EXPECT( b16u <= a16u );
    EXPECT( a16u <= a16u );
    EXPECT( a16u >= a16u );
    EXPECT( a16u >  b16u );

    EXPECT( a64u == a64u );
    EXPECT( a64u != b64u );
    EXPECT( b64u <  a64u );
    EXPECT( b64u <= a64u );
    EXPECT( a64u <= a64u );
    EXPECT( a64u >= a64u );
    EXPECT( a64u >  b64u );

    EXPECT( a80u == a80u );
    EXPECT( a80u != b80u );
    EXPECT( b80u <  a80u );
    EXPECT( b80u <= a80u );
    EXPECT( a80u <= a80u );
    EXPECT( a80u >= a80u );
    EXPECT( a80u >  b80u );

    EXPECT( a128u == a128u );
    EXPECT( a128u != b128u );
    EXPECT( b128u <  a128u );
    EXPECT( b128u <= a128u );
    EXPECT( a128u <= a128u );
    EXPECT( a128u >= a128u );
    EXPECT( a128u >  b128u );
  },

  CASE("uint constructors") {
    EXPECT( a16u == UInt<16>("0xcafe") );
    EXPECT( a16u == UInt<16>(a16u) );
    EXPECT( a64u == UInt<64>(a64u) );
    EXPECT( a80u == UInt<80>(a80u) );
    EXPECT( a128u == UInt<128>(a128u) );
    EXPECT( a16u == UInt<16>(0xfcafe) );
    EXPECT( UInt<128>(0x1) == UInt<128>("0x1") );
    EXPECT( a80u == UInt<80>(std::array<uint64_t,2>({0x9874, 0x26c1f7cd7d4d693a})) );
    EXPECT( a128u == UInt<128>(std::array<uint64_t,2>({0xe903646a697fcaa3, 0x44d2b2aa95e47b5d})) );
  },

  CASE("uint pad operator") {
    EXPECT( a16u == a16u.pad<16>() );
    EXPECT( a16u.pad<64>() == UInt<64>(0xcafe) );
    EXPECT( a64u.pad<200>() == a64u.pad<200>() );
    EXPECT( a64u.pad<200>() != b64u.pad<200>() );
  },

  CASE("uint cat operator") {
    EXPECT( a16u.cat(b16u) == UInt<32>(0xcafebebe) );
    EXPECT( a16u.cat(a64u) == UInt<80>("0xcafee2bd5b4ff8b30fc8") );
    EXPECT( a64u.cat(a16u) == UInt<80>("0xe2bd5b4ff8b30fc8cafe") );
    EXPECT( a16u.cat(a80u) == UInt<96>("0xcafe987426c1f7cd7d4d693a") );
    EXPECT( a80u.cat(a16u) == UInt<96>("0x987426c1f7cd7d4d693acafe") );
    EXPECT( a16u.cat(a128u) == UInt<144>("0xcafee903646a697fcaa344d2b2aa95e47b5d") );
    EXPECT( a128u.cat(a16u) == UInt<144>("0xe903646a697fcaa344d2b2aa95e47b5dcafe") );
    EXPECT( a80u.cat(a128u) == UInt<208>("0x987426c1f7cd7d4d693ae903646a697fcaa344d2b2aa95e47b5d") );
    EXPECT( a128u.cat(a80u) == UInt<208>("0xe903646a697fcaa344d2b2aa95e47b5d987426c1f7cd7d4d693a") );
    EXPECT( a128u.cat(b128u) == UInt<256>("0xe903646a697fcaa344d2b2aa95e47b5d56fa570ecb04adca42405f12bf28b822") );
  },

  CASE("uint add operator") {
    EXPECT( a16u + b16u == UInt<17>(0x189bc) );
    EXPECT( a64u + b64u == UInt<65>("0x11280af33351c486f") );
    EXPECT( a80u + b80u == UInt<81>("0xeeae2e199848f91fddbf") );
    EXPECT( a128u + b128u == UInt<129>("0x13ffdbb793484786d871311bd550d337f") );
  },

  CASE("uint addw operator") {
    EXPECT( a16u.addw(b16u) == UInt<16>(0x89bc) );
    EXPECT( a64u.addw(b64u) == UInt<64>("0x1280af33351c486f") );
    EXPECT( a80u.addw(b80u) == UInt<80>("0xeeae2e199848f91fddbf") );
    EXPECT( a128u.addw(b128u) == UInt<128>("0x3ffdbb793484786d871311bd550d337f") );
  },

  CASE("uint sub operator") {
    EXPECT( a16u - b16u == UInt<17>(0xc40) );
    EXPECT( a64u - b64u == UInt<65>("0xb2fa076cbc49d721") );
    EXPECT( a80u - b80u == UInt<81>("0x423a1f6a5752017af4b5") );
    EXPECT( a128u - b128u == UInt<129>("0x92090d5b9e7b1cd902925397d6bbc33b") );
  },

  CASE("uint negate operator") {
    EXPECT( -a16u == SInt<17>(0x13502) );
    EXPECT( -a64u == SInt<65>("0x11d42a4b0074cf038") );
    EXPECT( -a80u == SInt<81>("0x1678bd93e083282b296c6") );
    EXPECT( -a128u == SInt<129>("0x116fc9b959680355cbb2d4d556a1b84a3") );
    EXPECT( (-(-a16u)) == SInt<18>(a16u.pad<18>()) );
    EXPECT( (-(-a64u)) == SInt<66>(a64u.pad<66>()) );
    EXPECT( (-(-a80u)) == SInt<82>(a80u.pad<82>()) );
    EXPECT( (-(-a128u)) == SInt<130>(a128u.pad<130>()) );
  },

  CASE("uint mult operator") {
    EXPECT( a16u * b16u == UInt<32>(0x973f2c84) );
    EXPECT( a64u * b64u == UInt<128>("0x2a4dc44ce497c914d9d3df0ec14b0b78") );
    EXPECT( a80u * b80u == UInt<160>("0x335993b54d4bc81d37835773f77fa4765c79f322") );
    EXPECT( a128u * b128u == UInt<256>("0x4f2b00496d758f68469327504061b9045f77243f5cfda64ce9fb69abca8b3a5a") );
  },

  CASE("uint div operator") {
    EXPECT( a16u / b16u == UInt<16>(1) );
    EXPECT( a64u / b64u == UInt<64>(4) );
  },

  CASE("uint mod operator") {
    EXPECT( a16u % b16u == UInt<16>(0xc40) );
    EXPECT( a64u % b64u == UInt<64>(0x23b00bc3070e2d2c) );
  },

  CASE("uint not operator") {
    EXPECT( ~a16u == UInt<16>(0x3501) );
    EXPECT( ~a64u == UInt<64>(0x1d42a4b0074cf037) );
    EXPECT( ~a80u == UInt<80>("0x678bd93e083282b296c5") );
    EXPECT( ~a128u == UInt<128>("0x16fc9b959680355cbb2d4d556a1b84a2") );
  },

  CASE("uint and operator") {
    EXPECT( (a16u & b16u) == UInt<16>(0x8abe) );
    EXPECT( (a64u & b64u) == UInt<64>(0x2281534338210880) );
    EXPECT( (a80u & b80u) == UInt<80>("0x10300641a04979406000") );
    EXPECT( (a128u & b128u) == UInt<128>("0x4002440a490488824040120295203800") );
  },

  CASE("uint or operator") {
    EXPECT( (a16u | b16u) == UInt<16>(0xfefe) );
    EXPECT( (a64u | b64u) == UInt<64>(0xefff5beffcfb3fef) );
    EXPECT( (a80u | b80u) == UInt<80>("0xde7e27d7f7ff7fdf7dbf") );
    EXPECT( (a128u | b128u) == UInt<128>("0xfffb776eeb7fefeb46d2ffbabfecfb7f") );
  },

  CASE("uint xor operator") {
    EXPECT( (a16u ^ b16u) == UInt<16>(0x7440) );
    EXPECT( (a64u ^ b64u) == UInt<64>(0xcd7e08acc4da376f) );
    EXPECT( (a80u ^ b80u) == UInt<80>("0xce4e219657b6069f1dbf") );
    EXPECT( (a128u ^ b128u) == UInt<128>("0xbff93364a27b67690692edb82accc37f") );
  },

  CASE("uint andr operator") {
    EXPECT( (a16u.andr()) == UInt<1>(0x0) );
    EXPECT( ((~UInt<16>(0)).andr()) == UInt<1>(1) );
    EXPECT( (a64u.andr()) == UInt<1>(0x0) );
    EXPECT( ((~UInt<64>(0)).andr()) == UInt<1>(1) );
    EXPECT( (a80u.andr()) == UInt<1>(0x0) );
    EXPECT( ((~UInt<80>(0)).andr()) == UInt<1>(1) );
    EXPECT( (a128u.andr()) == UInt<1>(0x0) );
    EXPECT( ((~UInt<128>(0)).andr()) == UInt<1>(1) );
  },

  CASE("uint orr operator") {
    EXPECT( (a16u.orr()) == UInt<1>(0x1) );
    EXPECT( (UInt<16>(0).andr()) == UInt<1>(0) );
    EXPECT( (a64u.orr()) == UInt<1>(0x1) );
    EXPECT( (UInt<64>(0).andr()) == UInt<1>(0) );
    EXPECT( (a80u.orr()) == UInt<1>(0x1) );
    EXPECT( (UInt<80>(0).andr()) == UInt<1>(0) );
    EXPECT( (a128u.orr()) == UInt<1>(0x1) );
    EXPECT( (UInt<128>(0).andr()) == UInt<1>(0) );
  },

  CASE("uint xorr operator") {
    EXPECT( (a16u.xorr()) == UInt<1>(0x1) );
    EXPECT( (b16u.xorr()) == UInt<1>(0x0) );
    EXPECT( (a64u.xorr()) == UInt<1>(0x1) );
    EXPECT( (b64u.xorr()) == UInt<1>(0x0) );
    EXPECT( (a80u.xorr()) == UInt<1>(0x1) );
    EXPECT( (b80u.xorr()) == UInt<1>(0x1) );
    EXPECT( (a128u.xorr()) == UInt<1>(0x0) );
    EXPECT( (b128u.xorr()) == UInt<1>(0x1) );
  },

  CASE("uint bits operator") {
    EXPECT( (a16u.bits<11,4>()) == UInt<8>(0xaf) );
    EXPECT( (a64u.bits<47,24>()) == UInt<24>(0x5b4ff8) );
    EXPECT( (a80u.bits<79,64>()) == UInt<16>(0x9874) );
    EXPECT( (a80u.bits<71,56>()) == UInt<16>(0x7426) );
    EXPECT( (a128u.bits<111,96>()) == UInt<16>(0x646a) );
    EXPECT( (a128u.bits<71,56>()) == UInt<16>(0xa344) );
  },

  CASE("uint head operator") {
    EXPECT( (a16u.head<8>()) == UInt<8>(0xca) );
    EXPECT( (a64u.head<64>()) == a64u );
    EXPECT( (a64u.head<16>()) == UInt<16>(0xe2bd) );
    EXPECT( (a80u.head<24>()) == UInt<24>(0x987426) );
    EXPECT( (a128u.head<32>()) == UInt<32>(0xe903646a) );
  },

  CASE("uint tail operator") {
    EXPECT( (a16u.tail<8>()) == UInt<8>(0xfe) );
    EXPECT( (a64u.tail<0>()) == a64u );
    EXPECT( (a64u.tail<16>()) == UInt<48>(0x5b4ff8b30fc8) );
    EXPECT( (a80u.tail<8>()) == UInt<72>("0x7426c1f7cd7d4d693a") );
    EXPECT( (a128u.tail<32>()) == UInt<96>("0x697fcaa344d2b2aa95e47b5d") );
  },

  CASE("uint static shifts") {
    EXPECT( a16u.shl<0>() == a16u );
    EXPECT( a16u.shl<4>() == UInt<20>(0xcafe0) );
    EXPECT( a64u.shl<8>() == UInt<72>("0xe2bd5b4ff8b30fc800") );
    EXPECT( a80u.shl<60>() == UInt<140>("0x987426c1f7cd7d4d693a000000000000000") );
    EXPECT( a128u.shl<72>() == UInt<200>("0xe903646a697fcaa344d2b2aa95e47b5d000000000000000000") );

    EXPECT( a16u.shlw<0>() == a16u );
    EXPECT( a16u.shlw<4>() == UInt<16>(0xafe0) );
    EXPECT( a64u.shlw<8>() == UInt<64>("0xbd5b4ff8b30fc800") );
    EXPECT( a80u.shlw<60>() == UInt<80>("0xd693a000000000000000") );
    EXPECT( a128u.shlw<72>() == UInt<128>("0xd2b2aa95e47b5d000000000000000000") );

    EXPECT( a16u.shr<0>() == a16u );
    EXPECT( a16u.shr<8>() == UInt<8>(0xca) );
    EXPECT( a64u.shr<16>() == UInt<48>(0xe2bd5b4ff8b3) );
    EXPECT( a80u.shr<24>() == UInt<56>(0x987426c1f7cd7d) );
    EXPECT( a128u.shr<48>() == UInt<80>("0xe903646a697fcaa344d2"));
  },

  CASE("uint dynamic shifts") {
    EXPECT( (a16u << UInt<1>(0)) == UInt<17>(0xcafe) );
    EXPECT( (a16u << UInt<4>(4)) == UInt<31>(0xcafe0) );
    EXPECT( (a64u << UInt<4>(8)) == UInt<79>("0xe2bd5b4ff8b30fc800") );
    EXPECT( (a80u << UInt<5>(12)) == UInt<111>("0x987426c1f7cd7d4d693a000") );
    EXPECT( (a128u << UInt<6>(16)) == UInt<191>("0xe903646a697fcaa344d2b2aa95e47b5d0000") );

    EXPECT( (a16u.dshlw(UInt<1>(0))) == a16u );
    EXPECT( (a16u.dshlw(UInt<4>(4))) == UInt<16>(0xafe0) );
    EXPECT( (a64u.dshlw(UInt<4>(8))) == UInt<64>("0xbd5b4ff8b30fc800") );
    EXPECT( (a80u.dshlw(UInt<6>(60))) == UInt<80>("0xd693a000000000000000") );
    EXPECT( (a128u.dshlw(UInt<7>(72))) == UInt<128>("0xd2b2aa95e47b5d000000000000000000") );

    EXPECT( (a16u >> UInt<1>(0)) == UInt<16>(0xcafe) );
    EXPECT( (a16u >> UInt<4>(4)) == UInt<16>(0x0caf) );
    EXPECT( (a64u >> UInt<4>(8)) == UInt<64>("0xe2bd5b4ff8b30f") );
    EXPECT( (a80u >> UInt<5>(12)) == UInt<80>("0x987426c1f7cd7d4d6") );
    EXPECT( (a128u >> UInt<6>(16)) == UInt<128>("0xe903646a697fcaa344d2b2aa95e4") );
  },

  CASE("uint conversion") {
    EXPECT( a16u.asUInt() == a16u );
    EXPECT( a16u.asSInt() == SInt<16>("0xcafe") );
    EXPECT( a16u.cvt() == SInt<17>(0xcafe) );
  },

  CASE("sint comparison operators") {
    EXPECT( a16s == a16s );
    EXPECT( a16s != b16s );
    EXPECT( b16s <  a16s );
    EXPECT( b16s <= a16s );
    EXPECT( a16s <= a16s );
    EXPECT( a16s >= a16s );
    EXPECT( a16s >  b16s );

    EXPECT( a64s == a64s );
    EXPECT( a64s != b64s );
    EXPECT( b64s <  a64s );
    EXPECT( b64s <= a64s );
    EXPECT( a64s <= a64s );
    EXPECT( a64s >= a64s );
    EXPECT( a64s >  b64s );

    EXPECT( a80s == a80s );
    EXPECT( a80s != b80s );
    EXPECT( b80s <  a80s );
    EXPECT( b80s <= a80s );
    EXPECT( a80s <= a80s );
    EXPECT( a80s >= a80s );
    EXPECT( a80s >  b80s );

    EXPECT( a128s == a128s );
    EXPECT( a128s != b128s );
    EXPECT( b128s <  a128s );
    EXPECT( b128s <= a128s );
    EXPECT( a128s <= a128s );
    EXPECT( a128s >= a128s );
    EXPECT( a128s >  b128s );
  },

  CASE("sint constructors") {
    EXPECT( b16s == SInt<16>(0xccb2) );
    EXPECT( b16s == SInt<16>(b16s) );
    EXPECT( b64s == SInt<64>(b64s) );
    EXPECT( b80s == SInt<80>(b80s) );
    EXPECT( b128s == SInt<128>(b128s) );
    EXPECT( a80s == SInt<80>(std::array<uint64_t,2>({0x381c, 0x1fe6bca6875922fe})) );
    EXPECT( a128s == SInt<128>(std::array<uint64_t,2>({0x6e0939370acc19da, 0xec06e9c13db50674})) );
  },

  CASE("sint pad operator") {
    EXPECT( a16s == a16s.pad<16>() );
    EXPECT( a16s.pad<64>() == SInt<64>(0x6dba) );
    EXPECT( a64s.pad<200>() == a64s.pad<100>().pad<200>() );
    EXPECT( a64u.pad<200>() != b64u.pad<200>() );
    EXPECT( b16s.pad<64>() == SInt<64>(0xffffffffffffccb2) );
  },

  CASE("sint cat operator") {
    EXPECT( a16s.cat(b16s) == SInt<32>("0x6dbaccb2") );
    EXPECT( b16s.cat(b64s) == SInt<80>("0xccb2defaa415d9062302") );
    EXPECT( b64s.cat(b16s) == SInt<80>("0xdefaa415d9062302ccb2") );
    EXPECT( b16s.cat(b80s) == SInt<96>("0xccb2efbe8ae0d38ab7f36dda") );
    EXPECT( b80s.cat(b16s) == SInt<96>("0xefbe8ae0d38ab7f36ddaccb2") );
    EXPECT( b16s.cat(b128s) == SInt<144>("0xccb2beb828fdbac591dba8e38eeb433f563d") );
    EXPECT( b128s.cat(b16s) == SInt<144>("0xbeb828fdbac591dba8e38eeb433f563dccb2") );
    EXPECT( b80s.cat(b128s) == SInt<208>("0xefbe8ae0d38ab7f36ddabeb828fdbac591dba8e38eeb433f563d") );
    EXPECT( b128s.cat(b80s) == SInt<208>("0xbeb828fdbac591dba8e38eeb433f563defbe8ae0d38ab7f36dda") );
    EXPECT( b128s.cat(b128s) == SInt<256>("0xbeb828fdbac591dba8e38eeb433f563dbeb828fdbac591dba8e38eeb433f563d") );
  },

  CASE("sint add operator") {
    EXPECT( a16s + b16s == SInt<17>(0x3a6c) );
    EXPECT( b16s + b16s == SInt<17>(0x19964) );
    EXPECT( a64s + b64s == SInt<65>("0x5003313223626d04") );
    EXPECT( b64s + b64s == SInt<65>("0x1bdf5482bb20c4604") );
    EXPECT( a80s + b80s == SInt<81>("0x27daaac790313f4c90d8") );
    EXPECT( b80s + b80s == SInt<81>("0x1df7d15c1a7156fe6dbb4") );
    EXPECT( a128s + b128s == SInt<129>("0x2cc16234c591abb694ea78ac80f45cb1") );
    EXPECT( b128s + b128s == SInt<129>("0x17d7051fb758b23b751c71dd6867eac7a") );
    EXPECT( SInt<64>(1) + SInt<64>(-1) == SInt<65>(0) );
    EXPECT( SInt<64>(-1) + SInt<64>(-1) == SInt<65>(-2) );
  },

  CASE("sint addw operator") {
    EXPECT( a16s.addw(b16s) == SInt<16>(0x3a6c) );
    EXPECT( a64s.addw(b64s) == SInt<64>("0x5003313223626d04") );
    EXPECT( a80s.addw(b80s) == SInt<80>("0x27daaac790313f4c90d8") );
    EXPECT( a128s.addw(b128s) == SInt<128>("0x2cc16234c591abb694ea78ac80f45cb1") );
    EXPECT( SInt<64>(1).addw(SInt<64>(-1)) == SInt<64>(0) );
    EXPECT( SInt<64>(-1).addw(SInt<64>(-1)) == SInt<64>(-2) );
  },

  CASE("sint sub operator") {
    EXPECT( a16s - b16s == SInt<17>(0xa108) );
    EXPECT( b16s - a16s == SInt<17>(0x15ef8) );
    EXPECT( b16s - SInt<16>(0) == b16s.pad<17>() );
    EXPECT( a64s - b64s == SInt<65>("0x920de90671562700") );
    EXPECT( b64s - a64s == SInt<65>("0x16df216f98ea9d900") );
    EXPECT( b64s - SInt<64>(0) == b64s.pad<65>() );
    EXPECT( a80s - b80s == SInt<81>("0x485d9505e91bcf65b524") );
    EXPECT( b80s - a80s == SInt<81>("0x1b7a26afa16e4309a4adc") );
    EXPECT( b80s - SInt<80>(0) == b80s.pad<81>() );
    EXPECT( a128s - b128s == SInt<129>("0xaf511039500687ff43235ad5fa75b037") );
    EXPECT( b128s - a128s == SInt<129>("0x150aeefc6aff97800bcdca52a058a4fc9") );
    EXPECT( b128s - SInt<128>(0) == b128s.pad<129>() );
  },

  CASE("sint negate operator") {
    EXPECT( -a16s == SInt<17>(0x19246) );
    EXPECT( -a64s == SInt<65>("0x18ef772e3b5a3b5fe") );
    EXPECT( -a80s == SInt<81>("0x1c7e3e019435978a6dd02") );
    EXPECT( -a128s == SInt<129>("0x191f6c6c8f533e62513f9163ec24af98c") );
    EXPECT( (-(-a16s)) == SInt<18>(a16s.pad<18>()) );
    EXPECT( (-(-a64s)) == SInt<66>(a64s.pad<66>()) );
    EXPECT( (-(-a80s)) == SInt<82>(a80s.pad<82>()) );
    EXPECT( (-(-a128s)) == SInt<130>(a128s.pad<130>()) );

    EXPECT( -b16s == SInt<17>(0x334e) );
    EXPECT( -b64s == SInt<65>("0x21055bea26f9dcfe") );
    EXPECT( -b80s == SInt<81>("0x1041751f2c75480c9226") );
    EXPECT( -b128s == SInt<129>("0x4147d702453a6e24571c7114bcc0a9c3") );
    EXPECT( (-(-b16s)) == SInt<18>(b16s.pad<18>()) );
    EXPECT( (-(-b64s)) == SInt<66>(b64s.pad<66>()) );
    EXPECT( (-(-b80s)) == SInt<82>(b80s.pad<82>()) );
    EXPECT( (-(-b128s)) == SInt<130>(b128s.pad<130>()) );
  },

  CASE("sint mult operator") {
    EXPECT( a16s * b16s == SInt<32>(0xea028354) );
    EXPECT( a64s * b64s == SInt<128>("0xf16b880f2bad048691fd4b72a0e2da04") );
    EXPECT( a80s * b80s == SInt<160>("0xfc6fe531cae4d5f834f4831b7dc6f5fbfee7f24c") );
    EXPECT( a128s * b128s == SInt<256>("0xe3f0c77f6f1ce87a5d5735256c8addf7a2a5210cf49a1af0917e727f76d981a4") );
    EXPECT( b16s * b16s == SInt<32>(0xa482bc4) );
    EXPECT( b64s * b64s == SInt<128>("0x044261cf16323e9d07bfb5d30ce18c04") );
    EXPECT( b80s * b80s == SInt<160>("0x1083f6094f8beff28a26e6d6335b98f66ff5da4") );
    EXPECT( b128s * b128s == SInt<256>("0x10a58f581efee2a4d90812cc128d304f3a498bebb936e0afcbcc36cd7d130a89") );
    EXPECT( SInt<16>(-1) * SInt<16>(-1) == SInt<32>(1) );
    EXPECT( SInt<80>(-1) * SInt<80>(-1) == SInt<160>(1) );
    EXPECT( SInt<128>(-1) * SInt<128>(-1) == SInt<256>(1) );
    EXPECT( SInt<512>(-1) * SInt<512>(-1) == SInt<1024>(1) );
  },

  CASE("sint div operator") {
    EXPECT( a16s / b16s == SInt<17>(0x1fffe) );
    EXPECT( a64s / b64s == SInt<65>("0x1fffffffffffffffd") );
    EXPECT( a64s / a16s == SInt<65>("0x107b710ae332f") );
    EXPECT( b64s / b16s == SInt<65>("0xa4c48cb11e2b") );
  },

  CASE("sint mod operator") {
    EXPECT( a16s % b16s == SInt<16>(0x71e) );
    EXPECT( a64s % b64s == SInt<64>(0xdf8795dd56eb308) );
    EXPECT( a64s % a16s == SInt<16>(0x16dc) );
    EXPECT( b64s % b16s == SInt<16>(0xe51c) );
  },

  CASE("sint not operator") {
    EXPECT( ~a16s == UInt<16>(0x9245) );
    EXPECT( ~a64s == UInt<64>(0x8ef772e3b5a3b5fd) );
    EXPECT( ~a80s == UInt<80>("0xc7e3e019435978a6dd01") );
    EXPECT( ~a128s == UInt<128>("0x91f6c6c8f533e62513f9163ec24af98b") );
  },

  CASE("sint and operator") {
    EXPECT( (a16s & b16s) == UInt<16>(0x4cb2) );
    EXPECT( (a64s & b64s) == UInt<64>(0x5008841448040202L) );
    EXPECT( (a80s & b80s) == UInt<80>("0x281c0ae09082875120da") );
    EXPECT( (a128s & b128s) == UInt<128>("0x2e0828350ac411daa80288c101350634") );
  },

  CASE("sint or operator") {
    EXPECT( (a16s | b16s) == UInt<16>(0xedba) );
    EXPECT( (a64s | b64s) == UInt<64>(0xfffaad1ddb5e6b02) );
    EXPECT( (a80s | b80s) == UInt<80>("0xffbe9fe6ffaeb7fb6ffe") );
    EXPECT( (a128s | b128s) == UInt<128>("0xfeb939ffbacd99dbece7efeb7fbf567d") );
  },

  CASE("sint xor operator") {
    EXPECT( (a16s ^ b16s) == UInt<16>(0xa108) );
    EXPECT( (a64s ^ b64s) == UInt<64>(0xaff22909935a6900) );
    EXPECT( (a80s ^ b80s) == UInt<80>("0xd7a295066f2c30aa4f24") );
    EXPECT( (a128s ^ b128s) == UInt<128>("0xd0b111cab009880144e5672a7e8a5049") );
  },

  CASE("sint andr operator") {
    EXPECT( (a16s.andr()) == UInt<1>(0x0) );
    EXPECT( ((~UInt<16>(0)).asSInt().andr()) == UInt<1>(1) );
    EXPECT( (a64s.andr()) == UInt<1>(0x0) );
    EXPECT( ((~UInt<64>(0)).asSInt().andr()) == UInt<1>(1) );
    EXPECT( (a80s.andr()) == UInt<1>(0x0) );
    EXPECT( ((~UInt<80>(0)).asSInt().andr()) == UInt<1>(1) );
    EXPECT( (a128s.andr()) == UInt<1>(0x0) );
    EXPECT( ((~UInt<128>(0)).asSInt().andr()) == UInt<1>(1) );
  },

  CASE("sint orr operator") {
    EXPECT( (a16s.orr()) == UInt<1>(0x1) );
    EXPECT( (SInt<16>(0).andr()) == UInt<1>(0) );
    EXPECT( (a64s.orr()) == UInt<1>(0x1) );
    EXPECT( (SInt<64>(0).andr()) == UInt<1>(0) );
    EXPECT( (a80s.orr()) == UInt<1>(0x1) );
    EXPECT( (SInt<80>(0).andr()) == UInt<1>(0) );
    EXPECT( (a128s.orr()) == UInt<1>(0x1) );
    EXPECT( (SInt<128>(0).andr()) == UInt<1>(0) );
  },

  CASE("sint xorr operator") {
    EXPECT( (a16s.xorr()) == UInt<1>(0x0) );
    EXPECT( (b16s.xorr()) == UInt<1>(0x0) );
    EXPECT( (a64s.xorr()) == UInt<1>(0x1) );
    EXPECT( (b64s.xorr()) == UInt<1>(0x1) );
    EXPECT( (a80s.xorr()) == UInt<1>(0x0) );
    EXPECT( (b80s.xorr()) == UInt<1>(0x1) );
    EXPECT( (a128s.xorr()) == UInt<1>(0x1) );
    EXPECT( (b128s.xorr()) == UInt<1>(0x1) );
  },


  CASE("sint bits operator") {
    EXPECT( (a16s.bits<11,4>()) == UInt<8>(0xdb) );
    EXPECT( (a64s.bits<47,24>()) == UInt<24>(0x8d1c4a) );
    EXPECT( (a80s.bits<79,64>()) == UInt<16>(0x381c) );
    EXPECT( (a80s.bits<71,56>()) == UInt<16>(0x1c1f) );
    EXPECT( (a128s.bits<111,96>()) == UInt<16>(0x3937) );
    EXPECT( (a128s.bits<71,56>()) == UInt<16>(0xdaec) );
  },

  CASE("sint head operator") {
    EXPECT( (a16s.head<8>()) == UInt<8>(0x6d) );
    EXPECT( (a64s.head<64>()) == a64s.asUInt() );
    EXPECT( (a64s.head<16>()) == UInt<16>(0x7108) );
    EXPECT( (a80s.head<24>()) == UInt<24>(0x381c1f) );
    EXPECT( (a128s.head<32>()) == UInt<32>(0x6e093937) );

    EXPECT( (b16s.head<8>()) == UInt<8>(0xcc) );
    EXPECT( (b64s.head<16>()) == UInt<16>(0xdefa) );
    EXPECT( (b80s.head<24>()) == UInt<24>(0xefbe8a) );
    EXPECT( (b128s.head<32>()) == UInt<32>(0xbeb828fd) );
  },

  CASE("sint tail operator") {
    EXPECT( (a16s.tail<8>()) == UInt<8>(0xba) );
    EXPECT( (a64s.tail<0>()) == a64s.asUInt() );
    EXPECT( (a64s.tail<16>()) == UInt<48>(0x8d1c4a5c4a02) );
    EXPECT( (a80s.tail<8>()) == UInt<72>("0x1c1fe6bca6875922fe") );
    EXPECT( (a128s.tail<32>()) == UInt<96>("0x0acc19daec06e9c13db50674") );
  },

  CASE("sint static shifts") {
    EXPECT( a16s.shl<0>() == a16s );
    EXPECT( a16s.shl<4>() == SInt<20>(0x6dba0) );
    EXPECT( a64s.shl<8>() == SInt<72>("0x71088d1c4a5c4a0200") );
    EXPECT( a80s.shl<60>() == SInt<140>("0x381c1fe6bca6875922fe000000000000000") );
    EXPECT( a128s.shl<72>() == SInt<200>("0x6e0939370acc19daec06e9c13db50674000000000000000000") );

    EXPECT( a16s.shlw<0>() == a16s );
    EXPECT( a16s.shlw<4>() == SInt<16>(0xdba0) );
    EXPECT( a64s.shlw<8>() == SInt<64>("0x088d1c4a5c4a0200") );
    EXPECT( a80s.shlw<60>() == SInt<80>("0x922fe000000000000000") );
    EXPECT( a128s.shlw<72>() == SInt<128>("0x06e9c13db50674000000000000000000") );

    EXPECT( a16s.shr<0>() == a16s );
    EXPECT( a16s.shr<8>() == SInt<8>(0x6d) );
    EXPECT( a64s.shr<16>() == SInt<48>(0x71088d1c4a5c) );
    EXPECT( a80s.shr<24>() == SInt<56>(0x381c1fe6bca687) );
    EXPECT( a128s.shr<48>() == SInt<80>("0x6e0939370acc19daec06"));
  },

  CASE("sint dynamic shifts") {
    EXPECT( (a16s << UInt<1>(0)) == SInt<17>(0x6dba) );
    EXPECT( (a16s << UInt<4>(4)) == SInt<31>(0x6dba0) );
    EXPECT( (a64s << UInt<4>(8)) == SInt<79>("0x71088d1c4a5c4a0200") );
    EXPECT( (a80s << UInt<5>(12)) == SInt<111>("0x381c1fe6bca6875922fe000") );
    EXPECT( (a128s << UInt<6>(16)) == SInt<191>("0x6e0939370acc19daec06e9c13db506740000") );

    EXPECT( (b16s << UInt<1>(0)) == SInt<17>(0x1ccb2) );
    EXPECT( (b16s << UInt<4>(4)) == SInt<31>(0x7ffccb20) );
    EXPECT( (b64s << UInt<4>(8)) == SInt<79>("0x7fdefaa415d906230200") );
    EXPECT( (b80s << UInt<5>(12)) == SInt<111>("0x7ffffefbe8ae0d38ab7f36dda000") );
    EXPECT( (b128s << UInt<6>(16)) == SInt<191>("0x7fffffffffffbeb828fdbac591dba8e38eeb433f563d0000") );

    EXPECT( (a16s.dshlw(UInt<1>(0))) == SInt<16>(0x6dba) );
    EXPECT( (a16s.dshlw(UInt<4>(4))) == SInt<16>(0xdba0) );
    EXPECT( (a64s.dshlw(UInt<4>(8))) == SInt<64>("0x088d1c4a5c4a0200") );
    EXPECT( (a80s.dshlw(UInt<5>(12))) == SInt<80>("0xc1fe6bca6875922fe000") );
    EXPECT( (a128s.dshlw(UInt<6>(16))) == SInt<128>("0x39370acc19daec06e9c13db506740000") );

    EXPECT( (b16s.dshlw(UInt<1>(0))) == SInt<16>(0xccb2) );
    EXPECT( (b16s.dshlw(UInt<4>(4))) == SInt<16>(0xcb20) );
    EXPECT( (b64s.dshlw(UInt<4>(8))) == SInt<64>("0xfaa415d906230200") );
    EXPECT( (b80s.dshlw(UInt<6>(60))) == SInt<80>("0x36dda000000000000000") );
    EXPECT( (b128s.dshlw(UInt<7>(72))) == SInt<128>("0xe38eeb433f563d000000000000000000") );

    EXPECT( (a16s >> UInt<1>(0)) == SInt<16>(0x6dba) );
    EXPECT( (a16s >> UInt<4>(4)) == SInt<16>(0x06db) );
    EXPECT( (a64s >> UInt<4>(8)) == SInt<64>("0x71088d1c4a5c4a") );
    EXPECT( (a80s >> UInt<5>(12)) == SInt<80>("0x381c1fe6bca687592") );
    EXPECT( (a128s >> UInt<6>(16)) == SInt<128>("0x6e0939370acc19daec06e9c13db5") );

    EXPECT( (b16s >> UInt<1>(0)) == SInt<16>(0xccb2) );
    EXPECT( (b16s >> UInt<4>(4)) == SInt<16>(0xfccb) );
    EXPECT( (b64s >> UInt<4>(8)) == SInt<64>("0xffdefaa415d90623") );
    EXPECT( (b80s >> UInt<5>(12)) == SInt<80>("0xfffefbe8ae0d38ab7f36") );
    EXPECT( (b128s >> UInt<6>(16)) == SInt<128>("0xffffbeb828fdbac591dba8e38eeb433f") );
  },

  CASE("sint conversion") {
    EXPECT( a16s.asUInt() == UInt<16>("0x6dba") );
    EXPECT( a16s.asSInt() == a16s );
    EXPECT( a16s.cvt() == SInt<16>(0x6dba) );
  }
};

int main() {
  return lest::run(spec);
}
