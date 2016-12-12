/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: If included, all routines in the .c file placed into bank1
*/

#ifndef ZB_BANK_1_H
#define ZB_BANK_1_H 1

/*! \addtogroup ZB_OSIF */
/*! @{ */


#ifdef SDCC

#ifdef ZB_BANKED_BUILD
#pragma codeseg BANK1
#endif

#endif

/*! @} */

#endif /* ZB_BANK_1_H */
