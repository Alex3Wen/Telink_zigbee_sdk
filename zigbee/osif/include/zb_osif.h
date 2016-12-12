/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: Main header for OS and platform depenednt stuff
*/

#ifndef ZB_OSIF_H
#define ZB_OSIF_H 1

/*! \addtogroup ZB_OSIF */
/*! @{ */


#include "zb_osif_tc32.h"



#define MAIN() int main(int argc, char **argv)
#define FAKE_ARGV
#define ARGV_UNUSED ZVUNUSED(argc) ; ZVUNUSED(argv)
#define MAIN_RETURN(v) return (v)



#define  banked
#define ZB_CB_NAME_MACRO(a) a ## func

/**
   \par stub is function placed in the common bank which calls real function
   from anothe bank.
 */
#define ZB_CB_STUB(name)                                \
void ZB_CB_NAME_MACRO(name)(zb_uint8_t param) ; \
void name(zb_uint8_t param)                     \
{                                                       \
  ZB_CB_NAME_MACRO(name) (param);                          \
}


/*! @} */

#endif /* ZB_OSIF_H */
