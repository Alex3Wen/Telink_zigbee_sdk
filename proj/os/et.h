
//  event thread

/*
	Basically this is clone of proto thread from contiki, except that 
	et.h supplies no-return-value version to comply with the ev module.
	please refer to the proto thread documents
*/

#pragma once

#define ELC_INIT(s) 	s = 0;
#define ELC_RESUME(s) 	switch(s) { case 0:
#define ELC_SET(s) 		s = __LINE__; case __LINE__:
#define ELC_END(s) 		}


typedef struct{
    u16 lc;
}et_t;

/**
 * \name Initialization
 * @{
 */

/**
 * Initialize a protothread.
 *
 * Initializes a protothread. Initialization must be done prior to
 * starting to execute the protothread.
 *
 * \param et A pointer to the protothread control structure.
 *
 * \sa ET_SPAWN()
 *
 * \hideinitializer
 */
#define ET_INIT(et)   ELC_INIT((et)->lc)

/** @} */

/**
 * \name Declaration and definition
 * @{
 */

/**
 * Declaration of a protothread.
 *
 * This macro is used to declare a protothread. All protothreads must
 * be declared with this macro.
 *
 * \param name_args The name and arguments of the C function
 * implementing the protothread.
 *
 * \hideinitializer
 */
#define ET_THREAD(name_args) char name_args

/**
 * Declare the start of a protothread inside the C function
 * implementing the protothread.
 *
 * This macro is used to declare the starting point of a
 * protothread. It should be placed at the start of the function in
 * which the protothread runs. All C statements above the ET_BEGIN()
 * invokation will be executed each time the protothread is scheduled.
 *
 * \param et A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define ET_BEGIN(et) { char ET_YIELD_FLAG = 1; ELC_RESUME((et)->lc)

/**
 * Declare the end of a protothread.
 *
 * This macro is used for declaring that a protothread ends. It must
 * always be used together with a matching ET_BEGIN() macro.
 *
 * \param et A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define ET_END(et) ELC_END((et)->lc); ET_YIELD_FLAG = 0; 		\
                   ET_INIT(et); return; }

// with value returned version
#define ET_END_R(et,r) ELC_END((et)->lc); ET_YIELD_FLAG = 0; 	\
                   ET_INIT(et); return r; }

/** @} */

/**
 * \name Blocked wait
 * @{
 */

/**
 * Block and wait until condition is true.
 *
 * This macro blocks the protothread until the specified condition is
 * true.
 *
 * \param et A pointer to the protothread control structure.
 * \param condition The condition.
 *
 * \hideinitializer
 */
#define ET_WAIT_UNTIL(et, condition)	        \
  do {											\
    ELC_SET((et)->lc);							\
    if(!(condition)) {							\
      return;									\
    }											\
  } while(0)

// with value returned version
#define ET_WAIT_UNTIL_R(et, condition, r)       \
	  do {										\
		ELC_SET((et)->lc);						\
		if(!(condition)) {						\
		  return r;								\
		}										\
	  } while(0)
	

/**
 * Block and wait while condition is true.
 *
 * This function blocks and waits while condition is true. See
 * ET_WAIT_UNTIL().
 *
 * \param et A pointer to the protothread control structure.
 * \param cond The condition.
 *
 * \hideinitializer
 */
#define ET_WAIT_WHILE(et, cond)  		ET_WAIT_UNTIL((et), !(cond))
#define ET_WAIT_WHILE_R(et, cond, r)  	ET_WAIT_UNTIL_R((et), !(cond), r)

/** @} */

/**
 * \name Hierarchical protothreads
 * @{
 */

/**
 * Block and wait until a child protothread completes.
 *
 * This macro schedules a child protothread. The current protothread
 * will block until the child protothread completes.
 *
 * \note The child protothread must be manually initialized with the
 * ET_INIT() function before this function is used.
 *
 * \param et A pointer to the protothread control structure.
 * \param thread The child protothread with arguments
 *
 * \sa ET_SPAWN()
 *
 * \hideinitializer
 */
#define ET_WAIT_THREAD(et, thread) 		ET_WAIT_WHILE((et), ET_SCHEDULE(thread))
// with value returned version
#define ET_WAIT_THREAD_R(et, thread,r)	ET_WAIT_WHILE((et), ET_SCHEDULE(thread), r)

/**
 * Spawn a child protothread and wait until it exits.
 *
 * This macro spawns a child protothread and waits until it exits. The
 * macro can only be used within a protothread.
 *
 * \param et A pointer to the protothread control structure.
 * \param child A pointer to the child protothread's control structure.
 * \param thread The child protothread with arguments
 *
 * \hideinitializer
 */
#define ET_SPAWN(et, child, thread)		\
  do {									\
    ET_INIT((child));					\
    ET_WAIT_THREAD((et), (thread));		\
  } while(0)

// with value returned version
#define ET_SPAWN_R(et, child, thread, r)  \
	do {								  \
	  ET_INIT((child)); 				  \
	  ET_WAIT_THREAD((et), (thread), r);  \
	} while(0)

/** @} */

/**
 * \name Exiting and restarting
 * @{
 */

/**
 * Restart the protothread.
 *
 * This macro will block and cause the running protothread to restart
 * its execution at the place of the ET_BEGIN() call.
 *
 * \param et A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define ET_RESTART(et)				\
  do {								\
    ET_INIT(et);					\
    return;							\
  } while(0)

// with value returned version
#define ET_RESTART_R(et, r)			\
	do {							\
	  ET_INIT(et);					\
	  return r;						\
	} while(0)
  
/**
 * Exit the protothread.
 *
 * This macro causes the protothread to exit. If the protothread was
 * spawned by another protothread, the parent protothread will become
 * unblocked and can continue to run.
 *
 * \param et A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define ET_EXIT(et)				\
  do {							\
    ET_INIT(et);				\
    return;						\
  } while(0)

// with value returned version
#define ET_EXIT_R(et, r)		\
	do {						\
	  ET_INIT(et);				\
	  return r;					\
	} while(0)
  
/** @} */

/**
 * \name Calling a protothread
 * @{
 */

/**
 * Schedule a protothread.
 *
 * This function schedules a protothread. The return value of the
 * function is non-zero if the protothread is running or zero if the
 * protothread has exited.
 *
 * \param f The call to the C function implementing the protothread to
 * be scheduled
 *
 * \hideinitializer
 */
#define ET_SCHEDULE(f) ((f) < ET_EXITED)

/** @} */

/**
 * \name Yielding from a protothread
 * @{
 */

/**
 * Yield from the current protothread.
 *
 * This function will yield the protothread, thereby allowing other
 * processing to take place in the system.
 *
 * \param et A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define ET_YIELD(et)				\
  do {								\
    ET_YIELD_FLAG = 0;				\
    ELC_SET((et)->lc);				\
    if(ET_YIELD_FLAG == 0) {		\
      return;						\
    }								\
  } while(0)

// with value returned version
#define ET_YIELD_R(et, r)			\
	  do {							\
		ET_YIELD_FLAG = 0;			\
		ELC_SET((et)->lc);			\
		if(ET_YIELD_FLAG == 0) {	\
		  return r;					\
		}							\
	  } while(0)
	
/**
 * \brief      Yield from the protothread until a condition occurs.
 * \param et   A pointer to the protothread control structure.
 * \param cond The condition.
 *
 *             This function will yield the protothread, until the
 *             specified condition evaluates to true.
 *
 *
 * \hideinitializer
 */
#define ET_YIELD_UNTIL(et, cond)			\
  do {										\
    ET_YIELD_FLAG = 0;						\
    ELC_SET((et)->lc);						\
    if((ET_YIELD_FLAG == 0) || !(cond)) {	\
      return;								\
    }										\
  } while(0)

// with value returned version
#define ET_YIELD_UNTIL_R(et, cond, r)			\
	  do {										\
		ET_YIELD_FLAG = 0;						\
		ELC_SET((et)->lc);						\
		if((ET_YIELD_FLAG == 0) || !(cond)) {	\
		  return r;								\
		}										\
	  } while(0)
	

// this technique  combine the event system and the proto thread
// wait us then excute the next instruction...
#define ET_YIELD_TIME(pt, us)					\
	{											\
		static u32 ref; 						\
		ref = clock_time(); 					\
		while(1){								\
			if(clock_time_exceed(ref, us)){ 	\
				break;							\
			}									\
			ET_YIELD(pt);						\
		}										\
	}

// with value returned version
#define ET_YIELD_TIME_R(pt, us, r)				\
	{											\
		static u32 ref; 						\
		ref = clock_time(); 					\
		while(1){								\
			if(clock_time_exceed(ref, us)){ 	\
				break;							\
			}									\
			ET_YIELD_R(pt, r);					\
		}										\
	}
	

