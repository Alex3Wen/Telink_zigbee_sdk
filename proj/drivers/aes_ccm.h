#pragma  once

#define AES_BLOCK_SIZE     16

struct CCM_FLAGS_TAG {
    union {
        struct {
            u8 L : 3;
            u8 M : 3;
            u8 aData :1;
            u8 reserved :1;            
        } bf;
        u8 val;
    };
};

typedef struct CCM_FLAGS_TAG ccm_flags_t;

enum AES_OPT {
    AES_ENCRYPTION = 0,
    AES_DECRYPTION,
};


u8 aes_ccmAuthTran(u8 M, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u8 aStrLen, u8 *result);
u8 aes_ccmEncTran(u8 M, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u8 aStrLen, u8 *result);
u8 aes_ccmDecTran(u8 micLen, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u8 aStrLen, u8 *mic);
u8 aes_ccmDecAuthTran(u8 micLen, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u8 aStrLen, u8 *mic);

u8 hwAes_encrypt(u8 *key, u8 *data, u8 *result);
