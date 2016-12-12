
#include "../tl_common.h"
#include "utility.h"


/****************************************************************************
 * @fn          addrExtCmp
 *
 * @brief       Compare two extended addresses.
 *
 * input parameters
 *
 * @param       pAddr1        - Pointer to first address.
 * @param       pAddr2        - Pointer to second address.
 *
 * output parameters
 *
 * @return      TRUE if addresses are equal, FALSE otherwise
 */
u8 addrExtCmp(const u8 * pAddr1, const u8 * pAddr2)
{
  u8 i;

  for (i = EXT_ADDR_LEN; i != 0; i--)
  {
    if (*pAddr1++ != *pAddr2++)
    {
      return FALSE;
    }
  }
  return TRUE;
}


/****************************************************************************
 * @fn          sAddrCmp
 *
 * @brief       Compare two device addresses.
 *
 * input parameters
 *
 * @param       pAddr1        - Pointer to first address.
 * @param       pAddr2        - Pointer to second address.
 *
 * output parameters
 *
 * @return      TRUE if addresses are equal, FALSE otherwise
 */
u8 addrCmp(const addr_t *pAddr1, const addr_t *pAddr2)
{
  if (pAddr1->addrMode != pAddr2->addrMode)
  {
    return FALSE;
  }
  else if (pAddr1->addrMode == ADDR_MODE_NONE)
  {
    return FALSE;
  }
  else if (pAddr1->addrMode == ADDR_MODE_SHORT)
  {
    return (u8) (pAddr1->addr.shortAddr == pAddr2->addr.shortAddr);
  }
  else if (pAddr1->addrMode == ADDR_MODE_EXT)
  {
    return (addrExtCmp(pAddr1->addr.extAddr, pAddr2->addr.extAddr));
  }
  else
  {
    return FALSE;
  }
}



void addrCpy(addr_t *pDstAddr, addr_t* pSrcAddr)
{
    pDstAddr->addrMode = pSrcAddr->addrMode;
    if (pSrcAddr->addrMode == ADDR_MODE_SHORT) {
        pDstAddr->addr.shortAddr = pSrcAddr->addr.shortAddr;
    } else if (pSrcAddr->addrMode == ADDR_MODE_EXT) {
        memcpy(pDstAddr->addr.extAddr, pSrcAddr->addr.extAddr, EXT_ADDR_LEN);
    }
}


void generateRandomData(u8 *pData, u8 len)
{
	u8 i;
	for (i=0; i<len; i+=2) {
#ifdef WIN32
		*((u16*)(pData + i)) = (u16)my_random(); //randomT();
#else
		*((u16*)(pData + i)) = (u16)rand(); //randomT();
#endif

	}
}
