/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: If included, all routines in the .c file placed into common bank
*/

#ifndef ZB_BANK_COMMON_H
#define ZB_BANK_COMMON_H 1

/*! \addtogroup ZB_OSIF */
/*! @{ */

#ifdef SDCC

#ifdef ZB_BANKED_BUILD
#pragma codeseg HOME
#endif

#endif

/*! @} */

#endif /* ZB_BANK_COMMON_H */
