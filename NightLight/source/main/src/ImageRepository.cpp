//*************************************************************************************************
//
//  BITTAILOR.CH - NightLight
//
//-------------------------------------------------------------------------------------------------
//
//  ImageRepository
//  
//*************************************************************************************************

#include "ImageRepository.hpp"

#include <stdint.h>
#include <avr/pgmspace.h>

#include "Image.hpp"

//*************************************************************************************************

extern const uint32_t STAR[Image::SIZE][Image::SIZE] PROGMEM;
const uint32_t STAR[Image::SIZE][Image::SIZE] =
{
         {-16777216,-16777216,-16777216,-16777216,-16777216,-256,-256,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-256,-256,-256,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-256,-256},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-256,-256,-256,-256,-16777216,-16777216,-16777216,-256,-256,-256,-256},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-256,-256,-256,-256,-256,-16777216,-256,-256,-256,-256,-256},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-16777216},
         {-16777216,-16777216,-16777216,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-16777216},
         {-16777216,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-16777216,-16777216},
         {-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-16777216,-16777216,-16777216},
         {-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-16777216,-16777216,-16777216},
         {-16777216,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-256,-256,-256,-256,-256,-256,-256,-256,-256,-256,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-256,-256,-256,-256,-256,-16777216,-256,-256,-256,-256,-256},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-256,-256,-256,-256,-16777216,-16777216,-16777216,-256,-256,-256,-256},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-256,-256,-256,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-256,-256},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-256,-256,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216}
};

//*************************************************************************************************

extern const uint32_t TRUCK[Image::SIZE][Image::SIZE] PROGMEM;
const uint32_t TRUCK[Image::SIZE][Image::SIZE] =
{
         {-16777216,-16777216,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16777216,-16776961,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16777216,-16776961,-16776961,-16776961,-16777216,-16777216},
         {-16777216,-16777216,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16777216,-16776961,-16776961,-16776961,-16777216,-16777216},
         {-16777216,-16777216,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16777216,-16776961,-16776961,-16776961,-16777216,-16777216},
         {-16777216,-16777216,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16777216,-16776961,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16777216,-16776961,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16777216,-16776961,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16776961,-16776961,-16776961,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16777216,-16776961,-16776961,-16776961,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16776961,-16777216,-16777216,-16777216,-16776961,-16776961,-16777216,-16776961,-16776961,-16776961,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16776961,-16777216,-16777216,-16777216,-16776961,-16776961,-16776961,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16776961,-16776961,-16777216,-16777216,-16776961,-16776961,-16776961,-16776961,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16776961,-16776961,-16776961,-16776961,-16776961,-16776961,-16777216,-16777216,-16777216,-16777216}

};

//*************************************************************************************************

extern const uint32_t HEART[Image::SIZE][Image::SIZE] PROGMEM;
const uint32_t HEART[Image::SIZE][Image::SIZE] =
{
         {-16777216,-16777216,-16777216,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216},
         {-16777216,-16777216,-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216},
         {-16777216,-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216,-16777216},
         {-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-65536,-65536,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-65536,-65536,-65536,-65536,-65536,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216}

};

//*************************************************************************************************

extern const uint32_t CAR1[Image::SIZE][Image::SIZE] PROGMEM;
const uint32_t CAR1[Image::SIZE][Image::SIZE] =
{
         {-184549376,-33554432,-50331648,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16711681,-16711681,-16711681,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16711681,-16711681,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16711681,-16711681,-16711681,-16777216,-16711681,-16711681,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16711681,-16711681,-16711681,-16711681,-16777216,-16711681,-16711681,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16777216,-16777216,-16711681,-16711681,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16777216,-16777216,-16711681,-16711681,-16711681,-16711681,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16777216,-16777216,-16711681,-16711681,-16711681,-16711681,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16711681,-16711681,-16711681,-16711681,-16711681,-16711681,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16777216,-16777216,-16711681,-16711681,-16711681,-16711681,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16777216,-16777216,-16711681,-16711681,-16711681,-16711681,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16711681,-16711681,-16711681,-16711681,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16711681,-16711681,-16711681,-16777216,-16711681,-16711681,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16711681,-16777216,-16711681,-16711681,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16711681,-16711681,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711681,-16711681,-16777216,-16777216}
};

//*************************************************************************************************

extern const uint32_t CAR2[Image::SIZE][Image::SIZE] PROGMEM;
const uint32_t CAR2[Image::SIZE][Image::SIZE] =
{
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-65281,-65281,-65281,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-65281,-65281,-65281,-65281,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-65281,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216,-65281,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216,-65281,-16777216},
         {-16777216,-16777216,-16777216,-65281,-16777216,-16777216,-16777216,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216},
         {-16777216,-16777216,-65281,-16777216,-16777216,-16777216,-16777216,-65281,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216,-16777216},
         {-16777216,-65281,-65281,-16777216,-16777216,-16777216,-16777216,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216,-16777216},
         {-16777216,-65281,-65281,-16777216,-16777216,-16777216,-16777216,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216},
         {-16777216,-16777216,-65281,-65281,-16777216,-16777216,-16777216,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216,-65281,-16777216},
         {-16777216,-16777216,-16777216,-65281,-65281,-16777216,-16777216,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216,-65281,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-65281,-65281,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-65281,-65281,-65281,-65281,-65281,-16777216,-16777216,-16777216,-16777216,-16777216}
};

//*************************************************************************************************

extern const uint32_t CAR3[Image::SIZE][Image::SIZE] PROGMEM;
const uint32_t CAR3[Image::SIZE][Image::SIZE] =
{
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711936,-16711936,-16711936,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711936,-16711936,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16711936,-16777216,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16711936,-16777216,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16711936,-16777216,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16711936,-16777216,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16711936,-16777216,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16711936,-16777216,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16711936,-16777216,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711936,-16711936,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711936,-16711936,-16711936,-16711936,-16711936,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16711936,-16711936,-16711936,-16777216,-16777216,-16777216,-16777216,-16777216}



};

//*************************************************************************************************

extern const uint32_t ANGEL[Image::SIZE][Image::SIZE] PROGMEM;
const uint32_t ANGEL[Image::SIZE][Image::SIZE] =
{
         {-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-11310702,-15584133,-16044164,-16044165,-16044421,-15847301,-15124100,-12099699,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-7890765,-15254917,-16766335,-16700800,-16700800,-16635521,-16635777,-16701569,-16439174,-13480575,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-5194548,-12822649,-16241030,-16438147,-16569730,-16701057,-16635521,-16635778,-16701569,-16242057,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-16777216,-8088401,-10258276,-13545854,-16175752,-16635521,-16701056,-16636034,-16242314,-16777216,-16777216,-16777216,-14006658,-15453835,-14138755},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-8154452,-15847564,-16438917,-15584133,-11837041,-16777216,-14795912,-16308361,-16636805,-16702339,-16571014},
         {-16777216,-9534554,-15189125,-15321221,-10981738,-16777216,-7496782,-13348475,-14335104,-14926978,-16176263,-16570500,-16701826,-16636292,-16702084,-16702084},
         {-8613970,-15780226,-16765565,-16700285,-16569218,-8943450,-16777216,-14401154,-16504708,-16701571,-16636034,-16636034,-16636034,-16636291,-16636291,-16702083},
         {-11638634,-16437121,-16634238,-16634239,-16765822,-12625528,-16777216,-16176011,-16767103,-16635777,-16635778,-16635778,-16636034,-16636034,-16636034,-16636291},
         {-8679764,-15714690,-16765564,-16765308,-16568705,-9469534,-16777216,-13348989,-16373126,-16570243,-16635779,-16635778,-16635778,-16636034,-16636034,-16636034},
         {-16777216,-9797211,-15714695,-15977606,-10652775,-16777216,-3222307,-9666655,-12230771,-12362355,-14663812,-16307848,-16636034,-16636034,-16636034,-16570499},
         {-16777216,-16777216,-16777216,-16777216,-16777216,-6313026,-13151611,-15518341,-14729346,-8286294,-16777216,-11639151,-15913354,-16504709,-16570500,-16439174},
         {-16777216,-16777216,-7431245,-9600862,-13019513,-15649157,-16569218,-16766079,-16635266,-13677953,-16777216,-16777216,-16777216,-12231285,-13875329,-12559991},
         {-5523767,-13019514,-16240259,-16502656,-16568704,-16700031,-16634495,-16634752,-16700800,-14532484,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-8745815,-15451780,-16765564,-16700030,-16700030,-16700286,-16700287,-16700544,-16175495,-10521704,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216},
         {-16777216,-11573101,-15320450,-15517568,-15649152,-15714688,-15452032,-14202748,-9469277,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216,-16777216}
};

//*************************************************************************************************

//-------------------------------------------------------------------------------------------------

ImageRepository::ImageRepository() {

}

//-------------------------------------------------------------------------------------------------

ImageRepository::~ImageRepository() {

}

//-------------------------------------------------------------------------------------------------
