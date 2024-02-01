#ifndef __robosd_common_h
#define __robosd_common_h

#include "robosd_target_tuning.h"
#include "robosd_types.h"
#include "robosd_app_tuning.h"


#ifndef ROBO_EXPORT
#define ROBO_EXPORT
#endif

#ifndef ROBO_DECL
#define ROBO_DECL
#endif

#ifndef ROBO_DEBUG_EXPORT
#define ROBO_DEBUG_EXPORT
#endif

#ifndef ROBO_EXPORT_FUNCTION_PREFIX
#define ROBO_EXPORT_FUNCTION_PREFIX
#endif 

#ifndef ROBO_PLATFORM_INLINE
#define ROBO_PLATFORM_INLINE  static inline
#endif 

#ifndef RS
#define RS(x) (const robo_string_t)x
#endif

#endif
