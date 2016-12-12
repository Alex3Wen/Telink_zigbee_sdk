/***************************************************************************
*                                                                          *
* INSERT COPYRIGHT HERE!                                                   *
*                                                                          *
****************************************************************************
PURPOSE: Declare ring buffer internals
*/

#ifndef ZB_RINGBUFFER_H
#define ZB_RINGBUFFER_H 1

/*! \cond internals_doc */
/**
   @addtogroup ZB_BASE
   @{
*/


/**
   \par Generic ring buffer macros
 */

/**
   Declare ring buffer for entries of given type and capacity.
   This is typedef, not variable declaration.

   @param type_name_prefix - prefix for names (like xxx_s, xxx_t)
   @param ent_type - type of the ring buffer entry
   @param capacity - ring buffer capacity
 */
#define ZB_RING_BUFFER_DECLARE(type_name_prefix, ent_type, capacity)  \
typedef struct type_name_prefix ## _s                                 \
{                                                                     \
  ent_type       ring_buf[capacity];                                   \
  zb_ushort_t    read_i;                                               \
  zb_ushort_t    write_i;                                              \
  zb_ushort_t    written;                                              \
} type_name_prefix ## _t


/**
 * Initialize ring buffer internals
 */
#define ZB_RING_BUFFER_INIT(rb) ( (rb)->read_i = (rb)->write_i = (rb)->written = 0)

/**
 * Return ring buffer capacity
 *
 * @param rb - ring buffer pointer.
 */
#define ZB_RING_BUFFER_CAPACITY(rb) ((sizeof((rb)->ring_buf) / sizeof((rb)->ring_buf[0])))

/**
 * Return 1 if ring buffer is full
 *
 * @param rb - ring buffer pointer.
 */
#define ZB_RING_BUFFER_IS_FULL(rb) ((zb_uint_t)(rb)->written >= ZB_RING_BUFFER_CAPACITY(rb))

/**
 * Return 1 if ring buffer is empty
 *
 * @param rb - ring buffer pointer.
 */
#define ZB_RING_BUFFER_IS_EMPTY(rb) ((rb)->written == 0)


/**
 * Reserve slot in the ring buffer but do not update pointers
 *
 * @param rb -  ring buffer pointer.
 * @return Pointer to the ring buffer entry or NULL if ring buffer is full
 */
#define ZB_RING_BUFFER_PUT_RESERVE(rb)          \
(                                               \
  ZB_RING_BUFFER_IS_FULL(rb) ? NULL             \
  : (rb)->ring_buf + (rb)->write_i              \
  )

 /* TODO: remove ZB_RING_BUFFER_PUT_RESERVE and ZB_RING_BUFFER_FLUSH_PUT here and in *.c files
 use ZB_RING_BUFFER_IS_FULL and ZB_RING_BUFFER_PUT instead of it */

/**
 * Put to the ring buffer.
 * Get free slot from the ring buffer, return pointer to it.
 *
 * @param rb -  ring buffer pointer.
 * @return nothing
 */
#define ZB_RING_BUFFER_FLUSH_PUT(rb)                                    \
(                                                                       \
  (rb)->written++,                                                      \
  (rb)->write_i = ((rb)->write_i + 1) % ZB_RING_BUFFER_CAPACITY(rb)     \
  )

/**
 * Put value to the ring buffer.
 *
 * @param rb -  ring buffer pointer.
 * @value - value to put to ring buffer
 * @return nothing
 */
#define ZB_RING_BUFFER_PUT(rb, value)                                   \
(                                                                       \
  (rb)->ring_buf[(rb)->write_i] = (value),                              \
  (rb)->written++,                                                      \
  (rb)->write_i = ((rb)->write_i + 1) % ZB_RING_BUFFER_CAPACITY(rb)     \
  )

/**
 * Get entry from the ring buffer read pointer position
 *
 * @param rb -  ring buffer pointer.
 *
 * @return pointer to the ring buffer entry or NULL if it is empty
 */
#define ZB_RING_BUFFER_PEEK(rb)                 \
(                                               \
  ZB_RING_BUFFER_IS_EMPTY(rb) ? NULL            \
  : (rb)->ring_buf + (rb)->read_i               \
  )

/**
 * Get entry from the ring buffer read pointer position
 *
 * @param rb -  ring buffer pointer.
 *
 * @return pointer to the ring buffer entry
 */
#define ZB_RING_BUFFER_GET(rb)                 \
(                                               \
  (rb)->ring_buf + (rb)->read_i               \
  )

/**
 * Move ring buffer read pointer.
 *
 * To be used after ZB_RING_BUFFER_PEEK().
 * Note that this macro does not check for empty ring buffer.
 *
 * @param rb -  ring buffer pointer.
 * @return nothing
 */
#define ZB_RING_BUFFER_FLUSH_GET(rb)                                    \
(                                                                       \
  (rb)->written--,                                                      \
  ((rb)->read_i = ((rb)->read_i + 1) % ZB_RING_BUFFER_CAPACITY(rb))     \
  )

/*! @} */
/*! \endcond */

#endif /* ZB_RINGBUFFER_H */
