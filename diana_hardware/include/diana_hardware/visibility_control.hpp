#ifndef DIANA_HARDWARE__VISIBILITY_CONTROL_HPP_
#define DIANA_HARDWARE__VISIBILITY_CONTROL_HPP_

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DIANA_HARDWARE_EXPORT __attribute__((dllexport))
#define DIANA_HARDWARE_IMPORT __attribute__((dllimport))
#else
#define DIANA_HARDWARE_EXPORT __declspec(dllexport)
#define DIANA_HARDWARE_IMPORT __declspec(dllimport)
#endif

#ifdef DIANA_HARDWARE_BUILDING_DLL
#define DIANA_HARDWARE_PUBLIC DIANA_HARDWARE_EXPORT
#else
#define DIANA_HARDWARE_PUBLIC DIANA_HARDWARE_IMPORT
#endif

#define DIANA_HARDWARE_PUBLIC_TYPE DIANA_HARDWARE_PUBLIC
#define DIANA_HARDWARE_LOCAL

#else

#define DIANA_HARDWARE_EXPORT __attribute__((visibility("default")))
#define DIANA_HARDWARE_IMPORT
#if __GNUC__ >= 4
#define DIANA_HARDWARE_PUBLIC __attribute__((visibility("default")))
#define DIANA_HARDWARE_LOCAL __attribute__((visibility("hidden")))
#else
#define DIANA_HARDWARE_PUBLIC
#define DIANA_HARDWARE_LOCAL
#endif

#define DIANA_HARDWARE_PUBLIC_TYPE

#endif

#endif