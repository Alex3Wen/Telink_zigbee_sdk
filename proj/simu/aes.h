/*****************************************************************************//**
 * @file      mzspHostAesAPI.h
 * @brief    zigbee PC host AES API heade file.
 * @version  V0.0.01
 * @date     25. Aug 2011
 * @author   Embedded software Team
 *
 * @note
 * Copyright (C) 2011 Marvell Limited. All rights reserved.
 *
 * @par
 * Marvell Limited is supplying this software which provides customers with
 * programming information regarding the products.Marvell has no responsibility
 * or liability for the use of the software.Marvell not guarantee the correctness
 * of this software.Marvell reserves the right to make changes in the software
 * without notification.
 *
 ********************************************************************************
 * CHANGE HISTORY
 *
 *  dd/mmm/yy     Code Ver      Author     Description
 *
 *  18/Aug/11     V0.0.01         kjzhu       File created
 *
 *******************************************************************************/


#ifndef __MZSP_HOST_AES_API_H__
#define __MZSP_HOST_AES_API_H__


/** @addtogroup  zigBee_HOST_API
 *  @{
 */


/** @addtogroup  zigBee_HOST_AES_API 
 *  @{
 */


/** @defgroup zigBee_HOST_AES_API_Public_Types zigBee_HOST_AES_API_Public_Types
 *  @brief zigBee PC host API structure type definition
 *  @{
 */

 /**
 *  @brief zigBee API AES mode definition
 */
typedef enum aes_mode {
    AES_MODE_ECB = 0,        /*!< AES mode: ECB */
    AES_MODE_CBC,            /*!< AES mode: CBC */
    AES_MODE_CTR,            /*!< AES mode: CTR */
    AES_MODE_CCM = 5,        /*!< AES mode: CCM */
    AES_MODE_MMO,            /*!< AES mode: MMO */
    AES_MODE_BYPASS,         /*!< AES mode: Bypass */
    AES_END,
} aes_mode_t;

/**  
 *  @brief AES enc/dec select type definition 
 */                                                                                     
typedef enum aes_operation{                                                                         
    AES_STS_ENCRYPTION = 0,   /*!< AES ENC/DEC select: ENCRYPTION */                                                      
    AES_STS_DECRYPTION,       /*!< AES ENC/DEC select: DECRYPTION */                                                                                                                            
} aes_operation_t;                                                                                   


/**  
 *  @brief ECB mode configure type definition 
 */
typedef struct ecb_cfg {
    aes_operation_t op;       /*!< AES operation: Encryption or Decryption */
    u8  keyLen;          /*!< AES key size */
    u8  *key;            /*!< AES key content */
    u32 srcLen;          /*!< AES text length, the content of text is in the mzsp_aes parameter */
} ecb_cfg_t;

/**  
 *  @brief CBC mode configure type definition 
 */
typedef struct cbc_cfg {
    aes_operation_t op;        /*!< AES operation: Encryption or Decryption */
    u8 keyLen;            /*!< AES key size */
    u8 *key;              /*!< AES key content */
    u8 ivLen;             /*!< AES initialize vector length */
    u8 *iv;               /*!< AES initialize vector content */
    u8 micLen;            /*!< AES mic length */
    u8 *micE;             /*!< AES mic content, used in Encryption */
    u8 *micD;             /*!< AES mic content, used in Decryption */
    u32 srcLen;           /*!< AES text length, the content of text is in the mzsp_aes parameter */
} cbc_cfg_t;

/**  
 *  @brief CTR mode configure type definition 
 */
typedef struct ctr_cfg {
    aes_operation_t op;        /*!< AES operation: Encryption or Decryption */
    u8   keyLen;          /*!< AES key size */
    u8   *key;            /*!< AES key content */
    u8   ivLen;           /*!< AES initialize vector length */
    u8   *iv;             /*!< AES initialize vector content */
    u32  counterMod;      /*!< AES counter mod */
    u32  initCount;       /*!< AES initialize count */
    u32  srcLen;          /*!< AES text length, the content of text is in the mzsp_aes parameter */
} ctr_cfg_t;

/**  
 *  @brief MMO mode configure type definition 
 */
typedef struct mmo_cfg {
    aes_operation_t op;       /*!< AES operation: Encryption or Decryption */
    u8 keyLen;           /*!< AES key size */
    u8 *key;             /*!< AES key content */
    u32 srcLen;          /*!< AES text length, the content of text is in the mzsp_aes parameter */
} mmo_cfg_t;

/**  
 *  @brief CCM mode configure type definition 
 */
typedef struct ccm_cfg {
    aes_operation_t op;      /*!< AES operation: Encryption or Decryption */
    u8  keyLen;         /*!< AES key size */
    u8  *key;           /*!< AES key content */
    u8  ivLen;          /*!< AES initialize vector length */
    u8  *iv;            /*!< AES initialize vector content */
    u8  micLen;         /*!< AES mic length */
    u8  *micE;          /*!< AES mic content, used in Encryption */
    u8  *micD;          /*!< AES mic content, used in Decryption */
    u32 aStrLen;        /*!< AES aheader length */
    u8  *aStr;          /*!< AES aheader content */
    u32 srcLen;         /*!< AES text length, the content of text is in the mzsp_aes parameter */
} ccm_cfg_t;



/*@} end of group zigBee_HOST_AES_API_Public_Types definitions */



/** @defgroup Host_AES_API_Public_Function_Declaration API_Public_Function_Declaration
 *  @brief API functions statement
 *  @{
 */
 
/****************************************************************************//**
 * @brief soft aes
 *
 * @param[in]  aes mode/aes src string/aes parameter due to aes mode
 *
 * @param[out] aes result string
 *
 * @return status
 *
 *******************************************************************************/
u32 mzsp_aes(u8 aesMode, u8 * src, u8 * dst, void * parameter);


/*@} end of group Host_AES_API_Public_Function_Declaration */


/*@} end of group zigBee_HOST_AES_API  */


/*@} end of group zigBee_HOST_API */


#endif /* __MZSP_HOST_AES_API_H__ */
