# cmake/modules/TestSignalType.cmake
#
include(CheckFunctionExists)
include(CheckLibraryExists)
include(CheckIncludeFiles)
include(CheckIncludeFile)
include(CheckSymbolExists)
include(CheckCSourceRuns)
include(CheckCCompilerFlag)
include(CheckTypeSize)
include(CheckStructHasMember)
include(CMakeDependentOption)
include(FindPkgConfig)
include(GNUInstallDirs)

# Requires:
# - nada
# Optional:
# - THREADS opt
# Sets:
# PTHREAD_CFLAGS
# PTHREAD_LIBS
macro(CheckPTHREAD)
  if(PTHREADS)
    if(LINUX)
     MESSAGE(STATUS "MACRO CheckPTHREAD")
      set(PTHREAD_CFLAGS "-D_REENTRANT")
      set(PTHREAD_LDFLAGS "-pthread")
    elseif(BSDI)
      set(PTHREAD_CFLAGS "-D_REENTRANT -D_THREAD_SAFE")
      set(PTHREAD_LDFLAGS "")
    elseif(DARWIN)
      set(PTHREAD_CFLAGS "-D_THREAD_SAFE")
      # causes Carbon.p complaints?
      # set(PTHREAD_CFLAGS "-D_REENTRANT -D_THREAD_SAFE")
      set(PTHREAD_LDFLAGS "")
    elseif(FREEBSD)
      set(PTHREAD_CFLAGS "-D_REENTRANT -D_THREAD_SAFE")
      set(PTHREAD_LDFLAGS "-pthread")
    elseif(NETBSD)
      set(PTHREAD_CFLAGS "-D_REENTRANT -D_THREAD_SAFE")
      set(PTHREAD_LDFLAGS "-lpthread")
    elseif(OPENBSD)
      set(PTHREAD_CFLAGS "-D_REENTRANT")
      set(PTHREAD_LDFLAGS "-pthread")
    elseif(SOLARIS)
      set(PTHREAD_CFLAGS "-D_REENTRANT")
      set(PTHREAD_LDFLAGS "-pthread -lposix4")
    elseif(SYSV5)
      set(PTHREAD_CFLAGS "-D_REENTRANT -Kthread")
      set(PTHREAD_LDFLAGS "")
    elseif(AIX)
      set(PTHREAD_CFLAGS "-D_REENTRANT -mthreads")
      set(PTHREAD_LDFLAGS "-pthread")
    elseif(HPUX)
      set(PTHREAD_CFLAGS "-D_REENTRANT")
      set(PTHREAD_LDFLAGS "-L/usr/lib -pthread")
    elseif(HAIKU)
      set(PTHREAD_CFLAGS "-D_REENTRANT")
      set(PTHREAD_LDFLAGS "")
    else()
      set(PTHREAD_CFLAGS "-D_REENTRANT")
      set(PTHREAD_LDFLAGS "-lpthread")
    endif()

    # Run some tests
    set(ORIG_CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS}")
    set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} ${PTHREAD_CFLAGS} ${PTHREAD_LDFLAGS}")
    if(CMAKE_CROSSCOMPILING)
      set(HAVE_PTHREADS 1)
    else()
      check_c_source_runs("
        #include <pthread.h>
        int main(int argc, char** argv) {
          pthread_attr_t type;
          pthread_attr_init(&type);
          return 0;
        }" HAVE_PTHREADS)
    endif()
    if(HAVE_PTHREADS)
      MESSAGE(STATUS "MACRO CheckPTHREAD HAVE PTHREADS FOUND")
      set(SDL_THREAD_PTHREAD 1)
      list(APPEND EXTRA_CFLAGS ${PTHREAD_CFLAGS})
      list(APPEND EXTRA_LDFLAGS ${PTHREAD_LDFLAGS})
      set(SDL_CFLAGS "${SDL_CFLAGS} ${PTHREAD_CFLAGS}")
      list(APPEND SDL_LIBS ${PTHREAD_LDFLAGS})

      check_c_source_compiles("
        #include <pthread.h>
        int main(int argc, char **argv) {
          pthread_mutexattr_t attr;
          pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
          return 0;
        }" HAVE_RECURSIVE_MUTEXES)
      if(HAVE_RECURSIVE_MUTEXES)
      MESSAGE(STATUS "MACRO CheckPTHREAD HAVE RECURSIVE MUTEXES FOUND")
        set(KOL_THREAD_PTHREAD_RECURSIVE_MUTEX 1)
      else()
        check_c_source_compiles("
            #include <pthread.h>
            int main(int argc, char **argv) {
              pthread_mutexattr_t attr;
              pthread_mutexattr_setkind_np(&attr, PTHREAD_MUTEX_RECURSIVE_NP);
              return 0;
            }" HAVE_RECURSIVE_MUTEXES_NP)
        if(HAVE_RECURSIVE_MUTEXES_NP)
            MESSAGE(STATUS "MACRO CheckPTHREAD HAVE RECURSIVE MUTEXES NP FOUND")
          set(KOL_THREAD_PTHREAD_RECURSIVE_MUTEX_NP 1)
          else()
           MESSAGE(STATUS "MACRO CheckPTHREAD HAVE RECURSIVE MUTEXES NP FOUND")
        endif()
      endif()

      
        check_c_source_compiles("#include <pthread.h>
                                 #include <semaphore.h>
                                 int main(int argc, char **argv) { return 0; }" HAVE_PTHREADS_SEM)
        if(HAVE_PTHREADS_SEM)
          check_c_source_compiles("
              #include <pthread.h>
              #include <semaphore.h>
              int main(int argc, char **argv) {
                  sem_timedwait(NULL, NULL);
                  return 0;
              }" HAVE_SEM_TIMEDWAIT)
        endif()
      

      check_c_source_compiles("
          #include <pthread.h>
          #include <pthread_np.h>
          int main(int argc, char** argv) { return 0; }" HAVE_PTHREAD_NP_H)
      check_function_exists(pthread_setname_np HAVE_PTHREAD_SETNAME_NP)
      check_function_exists(pthread_set_name_np HAVE_PTHREAD_SET_NAME_NP)
      set(CMAKE_REQUIRED_FLAGS "${ORIG_CMAKE_REQUIRED_FLAGS}")
      
      
      set(HAVE_KOL_THREADS TRUE)
    endif()
  endif()
endmacro()



SET (PTHREADS ON)    
SET (LINUX ON)  
    
CheckPTHREAD()


#==============CANCEL======================
  MESSAGE(STATUS "Check for pthread_cancel")
  TRY_COMPILE(CMAKE_TEST_PTHREAD_CANCEL
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake/TestPthreadCancel.cpp
    LINK_LIBRARIES "-lpthread"
    OUTPUT_VARIABLE OUTPUT )
  IF (CMAKE_TEST_PTHREAD_CANCEL)
    MESSAGE(STATUS "Check for pthread_cancel  - found")
    SET (CANCEL_FOUND ON)

  ELSE (CMAKE_TEST_PTHREAD_CANCEL)
    MESSAGE(STATUS "Check for pthread_cancel  - not found")
    
  ENDIF (CMAKE_TEST_PTHREAD_CANCEL)
  
 #========SUSPEND======================== 
    MESSAGE(STATUS "Check for pthread_suspend")
  TRY_COMPILE(CMAKE_TEST_PTHREAD_SUSPEND
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake/TestPthreadSuspend.cpp
    LINK_LIBRARIES "-lpthread"
    OUTPUT_VARIABLE OUTPUT )
  IF (CMAKE_TEST_PTHREAD_SUSPEND)
    MESSAGE(STATUS "Check for pthread_suspend  - found")
    SET (SUSPEND_FOUND ON)

  ELSE (CMAKE_TEST_PTHREAD_SUSPEND)
    MESSAGE(STATUS "Check for pthread_suspend  - not found")
    
  ENDIF (CMAKE_TEST_PTHREAD_SUSPEND)

#========EXPIRATION========================   
   MESSAGE(STATUS "Check for pthread_expiration_np")
  TRY_COMPILE(CMAKE_TEST_PTHREAD_EXPIRATION_NP
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake/TestPthreadExpirationNP.cpp
    OUTPUT_VARIABLE OUTPUT)
  IF (CMAKE_TEST_PTHREAD_EXPIRATION_NP)
    MESSAGE(STATUS "Check for pthread_expiration_np  - found")
    SET (EXPIRATION_NP_FOUND ON)
    
  ELSE (CMAKE_TEST_PTHREAD_EXPIRATION_NP)
    MESSAGE(STATUS "Check for pthread_expiration_np  - not found")
    
  ENDIF (CMAKE_TEST_PTHREAD_EXPIRATION_NP)
  
 #========MUTEX TYPE========================  
 
   MESSAGE(STATUS "Check for mutex type")
  TRY_COMPILE(CMAKE_TEST_PTHREAD_TYPE_REC
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake/TestPthreadMutexTypeREC.cpp
    OUTPUT_VARIABLE OUTPUT)
  IF (CMAKE_TEST_PTHREAD_TYPE_REC)
    MESSAGE(STATUS "Check for mutex type recursive  - found")
    SET (MUTEX_LINUX ON)
    
  ELSE (CMAKE_TEST_PTHREAD_TYPE_REC)
    MESSAGE(STATUS "Check for mutex type recursive  - not found")
    
  ENDIF (CMAKE_TEST_PTHREAD_TYPE_REC)
 
   MESSAGE(STATUS "Check for mutex type 2")
  TRY_COMPILE(CMAKE_TEST_PTHREAD_TYPE_REC_NP
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake/TestPthreadMutexTypeREC_NP.cpp
    OUTPUT_VARIABLE OUTPUT)
  IF (CMAKE_TEST_PTHREAD_TYPE_REC_NP)
    MESSAGE(STATUS "Check for mutex type recursive NP - found")
    SET (MUTEX_NON_PORTABLE ON)
    
  ELSE (CMAKE_TEST_PTHREAD_TYPE_REC_NP)
    MESSAGE(STATUS "Check for mutex type recursive NP - not found")
    
  ENDIF (CMAKE_TEST_PTHREAD_TYPE_REC_NP)
 
    MESSAGE(STATUS "Check for mutex type 3")
  TRY_COMPILE(CMAKE_TEST_PTHREAD_TYPE_INITIALIZER_NP
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake/TestPthreadMutexTypeINI_NP.cpp
    OUTPUT_VARIABLE OUTPUT)
  IF (CMAKE_TEST_PTHREAD_TYPE_REC_INITIALIZER_NP)
    MESSAGE(STATUS "Check for mutex type recursive INITIALIZER - found")
    SET (MUTEX_APPLE_SOLARIS ON)
    
  ELSE (CMAKE_TEST_PTHREAD_TYPE_REC_INITIALIZER_NP)
    MESSAGE(STATUS "Check for mutex type recursive INITIALIZER - not found")
    
  ENDIF (CMAKE_TEST_PTHREAD_TYPE_REC_INITIALIZER_NP)
 
 
  MESSAGE(STATUS "Check for mutex type 4")
  TRY_COMPILE(CMAKE_TEST_PTHREAD_TYPE_COUNTING_FAST
    ${CMAKE_BINARY_DIR}
    ${CMAKE_SOURCE_DIR}/cmake/TestPthreadMutexTypeCOU.cpp
    OUTPUT_VARIABLE OUTPUT)
  IF (CMAKE_TEST_PTHREAD_TYPE_REC_COUNTING_FAST)
    MESSAGE(STATUS "Check for mutex type recursive Counting Fast - found")
    SET (NUTEX_CONTINUING ON)
    
  ELSE (CMAKE_TEST_PTHREAD_TYPE_REC_COUNTING_FAST)
    MESSAGE(STATUS "Check for mutex type recursive Counting Fast - not found")
    
  ENDIF (CMAKE_TEST_PTHREAD_TYPE_REC_COUNTING_FAST)
 
 
 

if(HAVE_PTHREADS_SEM)
file(APPEND ${CMAKE_SOURCE_DIR}/config.h "#define KOL_HAVE_PTHREAD_SEMAPHORE 1\n" )
    if(HAVE_SEM_TIMEDWAIT)
    file(APPEND ${CMAKE_SOURCE_DIR}/config.h "#define KOL_HAVE_PTHREAD_SEMAPHORE_TIMEDWAIT 1\n" )
    endif(HAVE_SEM_TIMEDWAIT)
else()
        
endif()
 
  
IF(SUSPEND_FOUND)
file(APPEND ${CMAKE_SOURCE_DIR}/config.h "#define KOL_HAVE_PTHREAD_SUSPEND 1\n" )
ELSE(SUSPEND_FOUND)
ENDIF(SUSPEND_FOUND)

IF(CANCEL_FOUND)
file(APPEND ${CMAKE_SOURCE_DIR}/config.h "#define KOL_HAVE_PTHREAD_CANCEL 1\n" )
ELSE(CANCEL_FOUND)
ENDIF(CANCEL_FOUND)


IF(EXPIRATION_NP_FOUND)

file(APPEND ${CMAKE_SOURCE_DIR}/config.h "#define KOL_PTHREAD_GET_EXPIRATION_NP 1\n" )
ELSE(EXPIRATION_NP_FOUND)
ENDIF(EXPIRATION_NP_FOUND)

IF(MUTEX_APPLE_SOLARIS)
#todo verify if there is library lthread, then set MUTEX_LINUX_ON
 SET (MUTEX_LINUX ON)
ENDIF(MUTEX_APPLE_SOLARIS)

IF(MUTEX_NON_PORTABLE)
file(APPEND ${CMAKE_SOURCE_DIR}/config.h "#define KOL_THREAD_PTHREAD_RECURSIVE_MUTEX 1\n" )
ELSEIF(MUTEX_LINUX)
file(APPEND ${CMAKE_SOURCE_DIR}/config.h "#define KOL_THREAD_PTHREAD_RECURSIVE_MUTEX 1\n" )
ELSEIF(NUTEX_CONTINUING)
file(APPEND ${CMAKE_SOURCE_DIR}/config.h "#define KOL_THREAD_PTHREAD_RECURSIVE_MUTEX 1\n" )
file(APPEND ${CMAKE_SOURCE_DIR}/config.h "#define MUTEX_TYPE_COUNTING_FAST 1\n" )
ENDIF()
    
if(KOL_THREAD_PTHREAD_RECURSIVE_MUTEX)
file(APPEND ${CMAKE_SOURCE_DIR}/config.h "#define KOL_THREAD_PTHREAD_RECURSIVE_MUTEX 1\n" ) 
else(KOL_THREAD_PTHREAD_RECURSIVE_MUTEX)

endif(KOL_THREAD_PTHREAD_RECURSIVE_MUTEX)

if(KOL_THREAD_PTHREAD_RECURSIVE_MUTEX_NP)
file(APPEND ${CMAKE_SOURCE_DIR}/config.h "#define KOL_THREAD_PTHREAD_RECURSIVE_MUTEX_NP 1\n" ) 
else(KOL_THREAD_PTHREAD_RECURSIVE_MUTEX_NP)

endif(KOL_THREAD_PTHREAD_RECURSIVE_MUTEX_NP)
 
