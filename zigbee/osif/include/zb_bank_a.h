/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: If included, all routines in the .c file placed into bank4
*/

#ifndef ZB_BANK_A_H
#define ZB_BANK_A_H

/*! \addtogroup ZB_OSIF */
/*! @{ */


#ifdef SDCC

#ifdef ZB_BANKED_BUILD
#pragma codeseg BANK10
#endif

#endif

/*! @} */

#endif /* ZB_BANK_A_H */
