/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: Macros for hash calculation
*/

#ifndef ZB_HASH_H
#define ZB_HASH_H 1

/*! \cond internals_doc */
/*! \addtogroup ZB_BASE */
/*! @{ */

#define ZB_HASH_MAGIC_VAL 5381u

/* TODO: check is this hash optimal for ints */
#define ZB_HASH_FUNC_STEP(hash_var, v) ((((hash_var) << 5) + (hash_var)) + (v))
#define ZB_4INT_HASH_FUNC(v1, v2, v3, v4) (ZB_HASH_FUNC_STEP(ZB_HASH_FUNC_STEP( ZB_HASH_FUNC_STEP( ZB_HASH_FUNC_STEP(ZB_HASH_MAGIC_VAL, (v1)), (v2)), (v3)), (v4)) & ZB_INT_MASK)
#define ZB_2INT_HASH_FUNC(v1, v2)      (ZB_HASH_FUNC_STEP(ZB_HASH_FUNC_STEP(ZB_HASH_MAGIC_VAL, (v1)), (v2)) & ZB_INT_MASK)

#define ZB_1INT_HASH_FUNC(v1)          (ZB_HASH_FUNC_STEP(ZB_HASH_MAGIC_VAL, (v1)) & ZB_INT_MASK)


/*! @} */
/*! \endcond */

#endif /* ZB_HASH_H */
