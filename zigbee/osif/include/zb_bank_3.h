/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: If included, all routines in the .c file placed into bank3
*/

#ifndef ZB_BANK3_H
#define ZB_BANK3_H 1

/*! \addtogroup ZB_OSIF */
/*! @{ */

#ifdef SDCC

#ifdef ZB_BANKED_BUILD
#pragma codeseg BANK3
#endif

#endif


/*! @} */

#endif /* ZB_BANK3_H */
