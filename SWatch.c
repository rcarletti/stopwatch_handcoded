/*
 * File: SWatch.c
 *
 * Code generated for Simulink model 'SWatch'.
 *
 * Model version                  : 1.56
 * Simulink Coder version         : 8.7 (R2014b) 08-Sep-2014
 * C/C++ source code generated on : Mon Dec  7 14:38:57 2015
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "SWatch.h"
#include "SWatch_private.h"

/* Named constants for Chart: '<S1>/SWatch' */
#define SWatch_IN_NO_ACTIVE_CHILD      ((uint8_T)0U)
#define SWatch_IN_alarmmode            ((uint8_T)1U)
#define SWatch_IN_check                ((uint8_T)1U)
#define SWatch_IN_freeze               ((uint8_T)1U)
#define SWatch_IN_pause                ((uint8_T)2U)
#define SWatch_IN_reset                ((uint8_T)3U)
#define SWatch_IN_running              ((uint8_T)4U)
#define SWatch_IN_sethours             ((uint8_T)1U)
#define SWatch_IN_setminutes           ((uint8_T)2U)
#define SWatch_IN_swatchmode           ((uint8_T)2U)
#define SWatch_IN_timemode             ((uint8_T)3U)
#define SWatch_IN_timesetmode          ((uint8_T)4U)
#define SWatch_event_Balarm            (5)
#define SWatch_event_Balarmset         (7)
#define SWatch_event_Bminus            (2)
#define SWatch_event_Bplus             (1)
#define SWatch_event_Bstop             (6)
#define SWatch_event_Btime             (3)
#define SWatch_event_Btimeset          (4)
#define SWatch_event_ptick             (0)

/* Forward declaration for local functions */
static void SWatc_enter_internal_swatchmode(uint8_T *SWatch_Y_hours, uint8_T
  *SWatch_Y_minutes, uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths,
  DW_SWatch_T *SWatch_DW);
static void SWatch_swatchmode(uint8_T *SWatch_Y_hours, uint8_T *SWatch_Y_minutes,
  uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths, uint8_T *SWatch_Y_mode,
  uint8_T *SWatch_Y_submode, DW_SWatch_T *SWatch_DW);
static void SWatch_timemode(uint8_T *SWatch_Y_hours, uint8_T *SWatch_Y_minutes,
  uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths, uint8_T *SWatch_Y_mode,
  uint8_T *SWatch_Y_submode, DW_SWatch_T *SWatch_DW);
static void SWatch_Control(uint8_T *SWatch_Y_hours, uint8_T *SWatch_Y_minutes,
  uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths, uint8_T *SWatch_Y_mode,
  uint8_T *SWatch_Y_submode, DW_SWatch_T *SWatch_DW);
static void SWatch_chartstep_c3_SWatch(uint8_T *SWatch_Y_hours, uint8_T
  *SWatch_Y_minutes, uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths,
  uint8_T *SWatch_Y_mode, uint8_T *SWatch_Y_buzzer, boolean_T
  *SWatch_Y_isalarmset, uint8_T *SWatch_Y_submode, DW_SWatch_T *SWatch_DW);

/* Function for Chart: '<S1>/SWatch' */
static void SWatc_enter_internal_swatchmode(uint8_T *SWatch_Y_hours, uint8_T
  *SWatch_Y_minutes, uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths,
  DW_SWatch_T *SWatch_DW)
{
  /* Entry Internal 'swatchmode': '<S3>:38' */
  switch (SWatch_DW->was_swatchmode) {
   case SWatch_IN_freeze:
    SWatch_DW->is_swatchmode = SWatch_IN_freeze;
    SWatch_DW->was_swatchmode = SWatch_IN_freeze;
    break;

   case SWatch_IN_pause:
    SWatch_DW->is_swatchmode = SWatch_IN_pause;
    SWatch_DW->was_swatchmode = SWatch_IN_pause;

    /* Entry 'pause': '<S3>:118' */
    SWatch_DW->Srunning = false;
    break;

   case SWatch_IN_reset:
    SWatch_DW->is_swatchmode = SWatch_IN_reset;
    SWatch_DW->was_swatchmode = SWatch_IN_reset;

    /* Entry 'reset': '<S3>:95' */
    SWatch_DW->Srunning = false;
    SWatch_DW->Shours = 0U;
    SWatch_DW->Sminutes = 0U;
    SWatch_DW->Sseconds = 0U;
    SWatch_DW->Stenths = 0U;
    *SWatch_Y_hours = SWatch_DW->Shours;
    *SWatch_Y_minutes = SWatch_DW->Sminutes;
    *SWatch_Y_seconds = SWatch_DW->Sseconds;
    *SWatch_Y_tenths = SWatch_DW->Stenths;
    break;

   case SWatch_IN_running:
    SWatch_DW->is_swatchmode = SWatch_IN_running;
    SWatch_DW->was_swatchmode = SWatch_IN_running;

    /* Entry 'running': '<S3>:96' */
    SWatch_DW->Srunning = true;
    break;

   default:
    /* Transition: '<S3>:284' */
    SWatch_DW->is_swatchmode = SWatch_IN_pause;
    SWatch_DW->was_swatchmode = SWatch_IN_pause;

    /* Entry 'pause': '<S3>:118' */
    SWatch_DW->Srunning = false;
    break;
  }
}

/* Function for Chart: '<S1>/SWatch' */
static void SWatch_swatchmode(uint8_T *SWatch_Y_hours, uint8_T *SWatch_Y_minutes,
  uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths, uint8_T *SWatch_Y_mode,
  uint8_T *SWatch_Y_submode, DW_SWatch_T *SWatch_DW)
{
  /* During 'swatchmode': '<S3>:38' */
  if (SWatch_DW->sfEvent == SWatch_event_Btimeset) {
    /* Transition: '<S3>:42' */
    /* Exit Internal 'swatchmode': '<S3>:38' */
    SWatch_DW->is_swatchmode = SWatch_IN_NO_ACTIVE_CHILD;
    SWatch_DW->is_Control = SWatch_IN_timesetmode;

    /* Entry 'timesetmode': '<S3>:23' */
    *SWatch_Y_mode = 1U;
    SWatch_DW->running = false;

    /* Entry Internal 'timesetmode': '<S3>:23' */
    /* Transition: '<S3>:62' */
    *SWatch_Y_minutes = SWatch_DW->minutes;
    SWatch_DW->is_timesetmode = SWatch_IN_sethours;

    /* Entry 'sethours': '<S3>:60' */
    *SWatch_Y_hours = SWatch_DW->hours;
    *SWatch_Y_submode = 1U;
  } else if (SWatch_DW->sfEvent == SWatch_event_Balarm) {
    /* Transition: '<S3>:48' */
    /* Exit Internal 'swatchmode': '<S3>:38' */
    SWatch_DW->is_swatchmode = SWatch_IN_NO_ACTIVE_CHILD;
    SWatch_DW->is_Control = SWatch_IN_alarmmode;

    /* Entry 'alarmmode': '<S3>:39' */
    *SWatch_Y_mode = 2U;
    *SWatch_Y_minutes = SWatch_DW->Aminutes;

    /* Entry Internal 'alarmmode': '<S3>:39' */
    /* Transition: '<S3>:82' */
    SWatch_DW->is_alarmmode = SWatch_IN_sethours;

    /* Entry 'sethours': '<S3>:76' */
    *SWatch_Y_hours = SWatch_DW->Ahours;
    *SWatch_Y_submode = 1U;
  } else {
    switch (SWatch_DW->is_swatchmode) {
     case SWatch_IN_freeze:
      /* During 'freeze': '<S3>:218' */
      if (SWatch_DW->sfEvent == SWatch_event_Bstop) {
        /* Transition: '<S3>:220' */
        SWatch_DW->is_swatchmode = SWatch_IN_running;
        SWatch_DW->was_swatchmode = SWatch_IN_running;

        /* Entry 'running': '<S3>:96' */
        SWatch_DW->Srunning = true;
      }
      break;

     case SWatch_IN_pause:
      /* During 'pause': '<S3>:118' */
      if (SWatch_DW->sfEvent == SWatch_event_Bplus) {
        /* Transition: '<S3>:120' */
        SWatch_DW->is_swatchmode = SWatch_IN_running;
        SWatch_DW->was_swatchmode = SWatch_IN_running;

        /* Entry 'running': '<S3>:96' */
        SWatch_DW->Srunning = true;
      } else {
        if (SWatch_DW->sfEvent == SWatch_event_Bminus) {
          /* Transition: '<S3>:121' */
          SWatch_DW->is_swatchmode = SWatch_IN_reset;
          SWatch_DW->was_swatchmode = SWatch_IN_reset;

          /* Entry 'reset': '<S3>:95' */
          SWatch_DW->Srunning = false;
          SWatch_DW->Shours = 0U;
          SWatch_DW->Sminutes = 0U;
          SWatch_DW->Sseconds = 0U;
          SWatch_DW->Stenths = 0U;
          *SWatch_Y_hours = SWatch_DW->Shours;
          *SWatch_Y_minutes = SWatch_DW->Sminutes;
          *SWatch_Y_seconds = SWatch_DW->Sseconds;
          *SWatch_Y_tenths = SWatch_DW->Stenths;
        }
      }
      break;

     case SWatch_IN_reset:
      /* During 'reset': '<S3>:95' */
      if (SWatch_DW->sfEvent == SWatch_event_Bplus) {
        /* Transition: '<S3>:97' */
        SWatch_DW->is_swatchmode = SWatch_IN_running;
        SWatch_DW->was_swatchmode = SWatch_IN_running;

        /* Entry 'running': '<S3>:96' */
        SWatch_DW->Srunning = true;
      }
      break;

     default:
      /* During 'running': '<S3>:96' */
      if (SWatch_DW->sfEvent == SWatch_event_Bminus) {
        /* Transition: '<S3>:117' */
        SWatch_DW->is_swatchmode = SWatch_IN_reset;
        SWatch_DW->was_swatchmode = SWatch_IN_reset;

        /* Entry 'reset': '<S3>:95' */
        SWatch_DW->Srunning = false;
        SWatch_DW->Shours = 0U;
        SWatch_DW->Sminutes = 0U;
        SWatch_DW->Sseconds = 0U;
        SWatch_DW->Stenths = 0U;
        *SWatch_Y_hours = SWatch_DW->Shours;
        *SWatch_Y_minutes = SWatch_DW->Sminutes;
        *SWatch_Y_seconds = SWatch_DW->Sseconds;
        *SWatch_Y_tenths = SWatch_DW->Stenths;
      } else if (SWatch_DW->sfEvent == SWatch_event_Bstop) {
        /* Transition: '<S3>:219' */
        SWatch_DW->is_swatchmode = SWatch_IN_freeze;
        SWatch_DW->was_swatchmode = SWatch_IN_freeze;
      } else if (SWatch_DW->sfEvent == SWatch_event_Bplus) {
        /* Transition: '<S3>:119' */
        SWatch_DW->is_swatchmode = SWatch_IN_pause;
        SWatch_DW->was_swatchmode = SWatch_IN_pause;

        /* Entry 'pause': '<S3>:118' */
        SWatch_DW->Srunning = false;
      } else {
        *SWatch_Y_hours = SWatch_DW->Shours;
        *SWatch_Y_minutes = SWatch_DW->Sminutes;
        *SWatch_Y_seconds = SWatch_DW->Sseconds;
        *SWatch_Y_tenths = SWatch_DW->Stenths;
      }
      break;
    }
  }
}

/* Function for Chart: '<S1>/SWatch' */
static void SWatch_timemode(uint8_T *SWatch_Y_hours, uint8_T *SWatch_Y_minutes,
  uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths, uint8_T *SWatch_Y_mode,
  uint8_T *SWatch_Y_submode, DW_SWatch_T *SWatch_DW)
{
  /* During 'timemode': '<S3>:22' */
  if (SWatch_DW->sfEvent == SWatch_event_Btimeset) {
    /* Transition: '<S3>:25' */
    SWatch_DW->is_Control = SWatch_IN_timesetmode;

    /* Entry 'timesetmode': '<S3>:23' */
    *SWatch_Y_mode = 1U;
    SWatch_DW->running = false;

    /* Entry Internal 'timesetmode': '<S3>:23' */
    /* Transition: '<S3>:62' */
    *SWatch_Y_minutes = SWatch_DW->minutes;
    SWatch_DW->is_timesetmode = SWatch_IN_sethours;

    /* Entry 'sethours': '<S3>:60' */
    *SWatch_Y_hours = SWatch_DW->hours;
    *SWatch_Y_submode = 1U;
  } else if (SWatch_DW->sfEvent == SWatch_event_Balarm) {
    /* Transition: '<S3>:47' */
    SWatch_DW->is_Control = SWatch_IN_alarmmode;

    /* Entry 'alarmmode': '<S3>:39' */
    *SWatch_Y_mode = 2U;
    *SWatch_Y_minutes = SWatch_DW->Aminutes;

    /* Entry Internal 'alarmmode': '<S3>:39' */
    /* Transition: '<S3>:82' */
    SWatch_DW->is_alarmmode = SWatch_IN_sethours;

    /* Entry 'sethours': '<S3>:76' */
    *SWatch_Y_hours = SWatch_DW->Ahours;
    *SWatch_Y_submode = 1U;
  } else if (SWatch_DW->sfEvent == SWatch_event_Bstop) {
    /* Transition: '<S3>:50' */
    SWatch_DW->is_Control = SWatch_IN_swatchmode;

    /* Entry 'swatchmode': '<S3>:38' */
    *SWatch_Y_mode = 3U;
    *SWatch_Y_hours = SWatch_DW->Shours;
    *SWatch_Y_minutes = SWatch_DW->Sminutes;
    *SWatch_Y_seconds = SWatch_DW->Sseconds;
    *SWatch_Y_tenths = SWatch_DW->Stenths;
    SWatc_enter_internal_swatchmode(SWatch_Y_hours, SWatch_Y_minutes,
      SWatch_Y_seconds, SWatch_Y_tenths, SWatch_DW);
  } else {
    if (SWatch_DW->sfEvent == SWatch_event_ptick) {
      /* Transition: '<S3>:58' */
      *SWatch_Y_hours = SWatch_DW->hours;
      *SWatch_Y_minutes = SWatch_DW->minutes;
      *SWatch_Y_seconds = SWatch_DW->seconds;
      *SWatch_Y_tenths = SWatch_DW->tenths;
    }
  }
}

/* Function for Chart: '<S1>/SWatch' */
static void SWatch_Control(uint8_T *SWatch_Y_hours, uint8_T *SWatch_Y_minutes,
  uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths, uint8_T *SWatch_Y_mode,
  uint8_T *SWatch_Y_submode, DW_SWatch_T *SWatch_DW)
{
  int32_T tmp;
  uint32_T qY;

  /* During 'Control': '<S3>:13' */
  if (SWatch_DW->sfEvent == SWatch_event_Btime) {
    /* Transition: '<S3>:45' */
    /* Exit Internal 'Control': '<S3>:13' */
    if (SWatch_DW->is_Control == SWatch_IN_timesetmode) {
      /* Exit Internal 'timesetmode': '<S3>:23' */
      SWatch_DW->is_timesetmode = SWatch_IN_NO_ACTIVE_CHILD;

      /* Exit 'timesetmode': '<S3>:23' */
      SWatch_DW->running = true;
      SWatch_DW->is_Control = SWatch_IN_NO_ACTIVE_CHILD;
    } else {
      SWatch_DW->is_Control = SWatch_IN_NO_ACTIVE_CHILD;

      /* Exit Internal 'alarmmode': '<S3>:39' */
      SWatch_DW->is_alarmmode = SWatch_IN_NO_ACTIVE_CHILD;

      /* Exit Internal 'swatchmode': '<S3>:38' */
      SWatch_DW->is_swatchmode = SWatch_IN_NO_ACTIVE_CHILD;
    }

    SWatch_DW->is_Control = SWatch_IN_timemode;

    /* Entry 'timemode': '<S3>:22' */
    *SWatch_Y_mode = 0U;
  } else {
    switch (SWatch_DW->is_Control) {
     case SWatch_IN_alarmmode:
      /* During 'alarmmode': '<S3>:39' */
      if (SWatch_DW->sfEvent == SWatch_event_Btimeset) {
        /* Transition: '<S3>:43' */
        /* Exit Internal 'alarmmode': '<S3>:39' */
        SWatch_DW->is_alarmmode = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_Control = SWatch_IN_timesetmode;

        /* Entry 'timesetmode': '<S3>:23' */
        *SWatch_Y_mode = 1U;
        SWatch_DW->running = false;

        /* Entry Internal 'timesetmode': '<S3>:23' */
        /* Transition: '<S3>:62' */
        *SWatch_Y_minutes = SWatch_DW->minutes;
        SWatch_DW->is_timesetmode = SWatch_IN_sethours;

        /* Entry 'sethours': '<S3>:60' */
        *SWatch_Y_hours = SWatch_DW->hours;
        *SWatch_Y_submode = 1U;
      } else if (SWatch_DW->sfEvent == SWatch_event_Bstop) {
        /* Transition: '<S3>:49' */
        /* Exit Internal 'alarmmode': '<S3>:39' */
        SWatch_DW->is_alarmmode = SWatch_IN_NO_ACTIVE_CHILD;
        SWatch_DW->is_Control = SWatch_IN_swatchmode;

        /* Entry 'swatchmode': '<S3>:38' */
        *SWatch_Y_mode = 3U;
        *SWatch_Y_hours = SWatch_DW->Shours;
        *SWatch_Y_minutes = SWatch_DW->Sminutes;
        *SWatch_Y_seconds = SWatch_DW->Sseconds;
        *SWatch_Y_tenths = SWatch_DW->Stenths;
        SWatc_enter_internal_swatchmode(SWatch_Y_hours, SWatch_Y_minutes,
          SWatch_Y_seconds, SWatch_Y_tenths, SWatch_DW);
      } else if (SWatch_DW->is_alarmmode == SWatch_IN_sethours) {
        /* During 'sethours': '<S3>:76' */
        if (SWatch_DW->sfEvent == SWatch_event_Balarm) {
          /* Transition: '<S3>:77' */
          SWatch_DW->is_alarmmode = SWatch_IN_setminutes;

          /* Entry 'setminutes': '<S3>:81' */
          *SWatch_Y_minutes = SWatch_DW->Aminutes;
          *SWatch_Y_submode = 2U;
        } else if (SWatch_DW->sfEvent == SWatch_event_Bplus) {
          /* Transition: '<S3>:83' */
          tmp = (int32_T)(SWatch_DW->Ahours + 1U);
          if ((uint32_T)tmp > 255U) {
            tmp = 255;
          }

          SWatch_DW->Ahours = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
            ((uint8_T)tmp / 24U * 24U));
          SWatch_DW->is_alarmmode = SWatch_IN_sethours;

          /* Entry 'sethours': '<S3>:76' */
          *SWatch_Y_hours = SWatch_DW->Ahours;
          *SWatch_Y_submode = 1U;
        } else if ((SWatch_DW->sfEvent == SWatch_event_Bminus) &&
                   (SWatch_DW->Ahours == 0)) {
          /* Transition: '<S3>:84' */
          SWatch_DW->Ahours = 23U;
          SWatch_DW->is_alarmmode = SWatch_IN_sethours;

          /* Entry 'sethours': '<S3>:76' */
          *SWatch_Y_hours = SWatch_DW->Ahours;
          *SWatch_Y_submode = 1U;
        } else {
          if (SWatch_DW->sfEvent == SWatch_event_Bminus) {
            /* Transition: '<S3>:86' */
            qY = SWatch_DW->Ahours - 1U;
            if (qY > SWatch_DW->Ahours) {
              qY = 0U;
            }

            SWatch_DW->Ahours = (uint8_T)qY;
            SWatch_DW->is_alarmmode = SWatch_IN_sethours;

            /* Entry 'sethours': '<S3>:76' */
            *SWatch_Y_hours = SWatch_DW->Ahours;
            *SWatch_Y_submode = 1U;
          }
        }
      } else {
        /* During 'setminutes': '<S3>:81' */
        if (SWatch_DW->sfEvent == SWatch_event_Balarm) {
          /* Transition: '<S3>:80' */
          SWatch_DW->is_alarmmode = SWatch_IN_sethours;

          /* Entry 'sethours': '<S3>:76' */
          *SWatch_Y_hours = SWatch_DW->Ahours;
          *SWatch_Y_submode = 1U;
        } else if (SWatch_DW->sfEvent == SWatch_event_Bplus) {
          /* Transition: '<S3>:79' */
          tmp = (int32_T)(SWatch_DW->Aminutes + 1U);
          if ((uint32_T)tmp > 255U) {
            tmp = 255;
          }

          SWatch_DW->Aminutes = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
            ((uint8_T)tmp / 60U * 60U));
          SWatch_DW->is_alarmmode = SWatch_IN_setminutes;

          /* Entry 'setminutes': '<S3>:81' */
          *SWatch_Y_minutes = SWatch_DW->Aminutes;
          *SWatch_Y_submode = 2U;
        } else if ((SWatch_DW->sfEvent == SWatch_event_Bminus) &&
                   (SWatch_DW->Aminutes == 0)) {
          /* Transition: '<S3>:85' */
          SWatch_DW->Aminutes = 59U;
          SWatch_DW->is_alarmmode = SWatch_IN_setminutes;

          /* Entry 'setminutes': '<S3>:81' */
          *SWatch_Y_minutes = SWatch_DW->Aminutes;
          *SWatch_Y_submode = 2U;
        } else {
          if (SWatch_DW->sfEvent == SWatch_event_Bminus) {
            /* Transition: '<S3>:78' */
            qY = SWatch_DW->Aminutes - 1U;
            if (qY > SWatch_DW->Aminutes) {
              qY = 0U;
            }

            SWatch_DW->Aminutes = (uint8_T)qY;
            SWatch_DW->is_alarmmode = SWatch_IN_setminutes;

            /* Entry 'setminutes': '<S3>:81' */
            *SWatch_Y_minutes = SWatch_DW->Aminutes;
            *SWatch_Y_submode = 2U;
          }
        }
      }
      break;

     case SWatch_IN_swatchmode:
      SWatch_swatchmode(SWatch_Y_hours, SWatch_Y_minutes, SWatch_Y_seconds,
                        SWatch_Y_tenths, SWatch_Y_mode, SWatch_Y_submode,
                        SWatch_DW);
      break;

     case SWatch_IN_timemode:
      SWatch_timemode(SWatch_Y_hours, SWatch_Y_minutes, SWatch_Y_seconds,
                      SWatch_Y_tenths, SWatch_Y_mode, SWatch_Y_submode,
                      SWatch_DW);
      break;

     default:
      /* During 'timesetmode': '<S3>:23' */
      if (SWatch_DW->sfEvent == SWatch_event_Balarm) {
        /* Transition: '<S3>:46' */
        /* Exit Internal 'timesetmode': '<S3>:23' */
        SWatch_DW->is_timesetmode = SWatch_IN_NO_ACTIVE_CHILD;

        /* Exit 'timesetmode': '<S3>:23' */
        SWatch_DW->running = true;
        SWatch_DW->is_Control = SWatch_IN_alarmmode;

        /* Entry 'alarmmode': '<S3>:39' */
        *SWatch_Y_mode = 2U;
        *SWatch_Y_minutes = SWatch_DW->Aminutes;

        /* Entry Internal 'alarmmode': '<S3>:39' */
        /* Transition: '<S3>:82' */
        SWatch_DW->is_alarmmode = SWatch_IN_sethours;

        /* Entry 'sethours': '<S3>:76' */
        *SWatch_Y_hours = SWatch_DW->Ahours;
        *SWatch_Y_submode = 1U;
      } else if (SWatch_DW->sfEvent == SWatch_event_Bstop) {
        /* Transition: '<S3>:51' */
        /* Exit Internal 'timesetmode': '<S3>:23' */
        SWatch_DW->is_timesetmode = SWatch_IN_NO_ACTIVE_CHILD;

        /* Exit 'timesetmode': '<S3>:23' */
        SWatch_DW->running = true;
        SWatch_DW->is_Control = SWatch_IN_swatchmode;

        /* Entry 'swatchmode': '<S3>:38' */
        *SWatch_Y_mode = 3U;
        *SWatch_Y_hours = SWatch_DW->Shours;
        *SWatch_Y_minutes = SWatch_DW->Sminutes;
        *SWatch_Y_seconds = SWatch_DW->Sseconds;
        *SWatch_Y_tenths = SWatch_DW->Stenths;
        SWatc_enter_internal_swatchmode(SWatch_Y_hours, SWatch_Y_minutes,
          SWatch_Y_seconds, SWatch_Y_tenths, SWatch_DW);
      } else if (SWatch_DW->is_timesetmode == SWatch_IN_sethours) {
        /* During 'sethours': '<S3>:60' */
        if (SWatch_DW->sfEvent == SWatch_event_Btimeset) {
          /* Transition: '<S3>:64' */
          SWatch_DW->is_timesetmode = SWatch_IN_setminutes;

          /* Entry 'setminutes': '<S3>:61' */
          *SWatch_Y_minutes = SWatch_DW->minutes;
          *SWatch_Y_submode = 2U;
        } else if (SWatch_DW->sfEvent == SWatch_event_Bplus) {
          /* Transition: '<S3>:66' */
          tmp = (int32_T)(SWatch_DW->hours + 1U);
          if ((uint32_T)tmp > 255U) {
            tmp = 255;
          }

          SWatch_DW->hours = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
            ((uint8_T)tmp / 24U * 24U));
          SWatch_DW->is_timesetmode = SWatch_IN_sethours;

          /* Entry 'sethours': '<S3>:60' */
          *SWatch_Y_hours = SWatch_DW->hours;
          *SWatch_Y_submode = 1U;
        } else if ((SWatch_DW->sfEvent == SWatch_event_Bminus) &&
                   (SWatch_DW->hours == 0)) {
          /* Transition: '<S3>:68' */
          SWatch_DW->hours = 23U;
          SWatch_DW->is_timesetmode = SWatch_IN_sethours;

          /* Entry 'sethours': '<S3>:60' */
          *SWatch_Y_hours = SWatch_DW->hours;
          *SWatch_Y_submode = 1U;
        } else {
          if (SWatch_DW->sfEvent == SWatch_event_Bminus) {
            /* Transition: '<S3>:72' */
            qY = SWatch_DW->hours - 1U;
            if (qY > SWatch_DW->hours) {
              qY = 0U;
            }

            SWatch_DW->hours = (uint8_T)qY;
            SWatch_DW->is_timesetmode = SWatch_IN_sethours;

            /* Entry 'sethours': '<S3>:60' */
            *SWatch_Y_hours = SWatch_DW->hours;
            *SWatch_Y_submode = 1U;
          }
        }
      } else {
        /* During 'setminutes': '<S3>:61' */
        if (SWatch_DW->sfEvent == SWatch_event_Btimeset) {
          /* Transition: '<S3>:65' */
          SWatch_DW->is_timesetmode = SWatch_IN_sethours;

          /* Entry 'sethours': '<S3>:60' */
          *SWatch_Y_hours = SWatch_DW->hours;
          *SWatch_Y_submode = 1U;
        } else if (SWatch_DW->sfEvent == SWatch_event_Bplus) {
          /* Transition: '<S3>:67' */
          tmp = (int32_T)(SWatch_DW->minutes + 1U);
          if ((uint32_T)tmp > 255U) {
            tmp = 255;
          }

          SWatch_DW->minutes = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
            ((uint8_T)tmp / 60U * 60U));
          SWatch_DW->is_timesetmode = SWatch_IN_setminutes;

          /* Entry 'setminutes': '<S3>:61' */
          *SWatch_Y_minutes = SWatch_DW->minutes;
          *SWatch_Y_submode = 2U;
        } else if ((SWatch_DW->sfEvent == SWatch_event_Bminus) &&
                   (SWatch_DW->minutes == 0)) {
          /* Transition: '<S3>:69' */
          SWatch_DW->minutes = 59U;
          SWatch_DW->is_timesetmode = SWatch_IN_setminutes;

          /* Entry 'setminutes': '<S3>:61' */
          *SWatch_Y_minutes = SWatch_DW->minutes;
          *SWatch_Y_submode = 2U;
        } else {
          if (SWatch_DW->sfEvent == SWatch_event_Bminus) {
            /* Transition: '<S3>:75' */
            qY = SWatch_DW->minutes - 1U;
            if (qY > SWatch_DW->minutes) {
              qY = 0U;
            }

            SWatch_DW->minutes = (uint8_T)qY;
            SWatch_DW->is_timesetmode = SWatch_IN_setminutes;

            /* Entry 'setminutes': '<S3>:61' */
            *SWatch_Y_minutes = SWatch_DW->minutes;
            *SWatch_Y_submode = 2U;
          }
        }
      }
      break;
    }
  }
}

/* Function for Chart: '<S1>/SWatch' */
static void SWatch_chartstep_c3_SWatch(uint8_T *SWatch_Y_hours, uint8_T
  *SWatch_Y_minutes, uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths,
  uint8_T *SWatch_Y_mode, uint8_T *SWatch_Y_buzzer, boolean_T
  *SWatch_Y_isalarmset, uint8_T *SWatch_Y_submode, DW_SWatch_T *SWatch_DW)
{
  int32_T tmp;

  /* During: SWatch/SWatch */
  SWatch_Control(SWatch_Y_hours, SWatch_Y_minutes, SWatch_Y_seconds,
                 SWatch_Y_tenths, SWatch_Y_mode, SWatch_Y_submode, SWatch_DW);

  /* During 'Timers': '<S3>:14' */
  /* During 'Clock': '<S3>:17' */
  if (SWatch_DW->running && (SWatch_DW->sfEvent == SWatch_event_ptick)) {
    /* Transition: '<S3>:271' */
    tmp = (int32_T)(SWatch_DW->tenths + 1U);
    if ((uint32_T)tmp > 255U) {
      tmp = 255;
    }

    SWatch_DW->tenths = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)((uint8_T)
      tmp / 10U * 10U));
    if (SWatch_DW->tenths == 0) {
      /* Transition: '<S3>:257' */
      tmp = (int32_T)(SWatch_DW->seconds + 1U);
      if ((uint32_T)tmp > 255U) {
        tmp = 255;
      }

      SWatch_DW->seconds = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)((uint8_T)
        tmp / 60U * 60U));
      if (SWatch_DW->seconds == 0) {
        /* Transition: '<S3>:270' */
        tmp = (int32_T)(SWatch_DW->minutes + 1U);
        if ((uint32_T)tmp > 255U) {
          tmp = 255;
        }

        SWatch_DW->minutes = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
          ((uint8_T)tmp / 60U * 60U));
        if (SWatch_DW->minutes == 0) {
          /* Transition: '<S3>:263' */
          tmp = (int32_T)(SWatch_DW->hours + 1U);
          if ((uint32_T)tmp > 255U) {
            tmp = 255;
          }

          SWatch_DW->hours = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
            ((uint8_T)tmp / 24U * 24U));
        }
      }
    }
  }

  /* During 'Stopwatch': '<S3>:239' */
  if (SWatch_DW->Srunning && (SWatch_DW->sfEvent == SWatch_event_ptick)) {
    /* Transition: '<S3>:254' */
    tmp = (int32_T)(SWatch_DW->Stenths + 1U);
    if ((uint32_T)tmp > 255U) {
      tmp = 255;
    }

    SWatch_DW->Stenths = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)((uint8_T)
      tmp / 10U * 10U));
    if (SWatch_DW->Stenths == 0) {
      /* Transition: '<S3>:241' */
      tmp = (int32_T)(SWatch_DW->Sseconds + 1U);
      if ((uint32_T)tmp > 255U) {
        tmp = 255;
      }

      SWatch_DW->Sseconds = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
        ((uint8_T)tmp / 60U * 60U));
      if (SWatch_DW->Sseconds == 0) {
        /* Transition: '<S3>:253' */
        tmp = (int32_T)(SWatch_DW->Sminutes + 1U);
        if ((uint32_T)tmp > 255U) {
          tmp = 255;
        }

        SWatch_DW->Sminutes = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
          ((uint8_T)tmp / 60U * 60U));
        if (SWatch_DW->Sminutes == 0) {
          /* Transition: '<S3>:246' */
          tmp = (int32_T)(SWatch_DW->Shours + 1U);
          if ((uint32_T)tmp > 255U) {
            tmp = 255;
          }

          SWatch_DW->Shours = (uint8_T)((uint32_T)(uint8_T)tmp - (uint8_T)
            ((uint8_T)tmp / 100U * 100U));
        }
      }
    }
  }

  /* During 'AlarmMng': '<S3>:15' */
  /* During 'check': '<S3>:122' */
  if ((SWatch_DW->sfEvent == SWatch_event_ptick) && (SWatch_DW->hours ==
       SWatch_DW->Ahours) && (SWatch_DW->minutes == SWatch_DW->Aminutes) &&
      (*SWatch_Y_isalarmset)) {
    /* Transition: '<S3>:125' */
    *SWatch_Y_buzzer = 1U;
    SWatch_DW->is_AlarmMng = SWatch_IN_check;
  } else {
    if (SWatch_DW->sfEvent == SWatch_event_Balarmset) {
      /* Transition: '<S3>:294' */
      *SWatch_Y_isalarmset = !*SWatch_Y_isalarmset;
      *SWatch_Y_buzzer = 0U;
      SWatch_DW->is_AlarmMng = SWatch_IN_check;
    }
  }
}

/* Model step function */
void SWatch_step(RT_MODEL_SWatch_T *const SWatch_M, boolean_T SWatch_U_Bplus,
                 boolean_T SWatch_U_Bminus, boolean_T SWatch_U_Btime, boolean_T
                 SWatch_U_Btimeset, boolean_T SWatch_U_Balarm, boolean_T
                 SWatch_U_Bswatch, boolean_T SWatch_U_Balarmset, uint8_T
                 *SWatch_Y_hours, uint8_T *SWatch_Y_minutes, uint8_T
                 *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths, uint8_T
                 *SWatch_Y_mode, uint8_T *SWatch_Y_buzzer, boolean_T
                 *SWatch_Y_isalarmset, uint8_T *SWatch_Y_submode)
{
  DW_SWatch_T *SWatch_DW = ((DW_SWatch_T *) SWatch_M->ModelData.dwork);
  PrevZCX_SWatch_T *SWatch_PrevZCX = ((PrevZCX_SWatch_T *)
    SWatch_M->ModelData.prevZCSigState);
  uint8_T rtb_FixPtSum1;
  boolean_T zcEvent[8];
  boolean_T tmp;
  int32_T i;

  /* Chart: '<S1>/SWatch' incorporates:
   *  TriggerPort: '<S3>/ input events '
   */
  /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
   *  UnitDelay: '<S2>/Output'
   */
  zcEvent[0] = (((SWatch_DW->Output_DSTATE != 0) !=
                 (SWatch_PrevZCX->SWatch_Trig_ZCE[0] == POS_ZCSIG)) &&
                (SWatch_PrevZCX->SWatch_Trig_ZCE[0] != UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/Bplus' */
  zcEvent[1] = (((SWatch_PrevZCX->SWatch_Trig_ZCE[1] == POS_ZCSIG) !=
                 SWatch_U_Bplus) && (SWatch_PrevZCX->SWatch_Trig_ZCE[1] !=
    UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/Bminus' */
  zcEvent[2] = (((SWatch_PrevZCX->SWatch_Trig_ZCE[2] == POS_ZCSIG) !=
                 SWatch_U_Bminus) && (SWatch_PrevZCX->SWatch_Trig_ZCE[2] !=
    UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/Btime' */
  zcEvent[3] = (((SWatch_PrevZCX->SWatch_Trig_ZCE[3] == POS_ZCSIG) !=
                 SWatch_U_Btime) && (SWatch_PrevZCX->SWatch_Trig_ZCE[3] !=
    UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/Btimeset' */
  zcEvent[4] = (((SWatch_PrevZCX->SWatch_Trig_ZCE[4] == POS_ZCSIG) !=
                 SWatch_U_Btimeset) && (SWatch_PrevZCX->SWatch_Trig_ZCE[4] !=
    UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/Balarm' */
  zcEvent[5] = (((SWatch_PrevZCX->SWatch_Trig_ZCE[5] == POS_ZCSIG) !=
                 SWatch_U_Balarm) && (SWatch_PrevZCX->SWatch_Trig_ZCE[5] !=
    UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/Bswatch' */
  zcEvent[6] = (((SWatch_PrevZCX->SWatch_Trig_ZCE[6] == POS_ZCSIG) !=
                 SWatch_U_Bswatch) && (SWatch_PrevZCX->SWatch_Trig_ZCE[6] !=
    UNINITIALIZED_ZCSIG));

  /* Inport: '<Root>/Balarmset' */
  zcEvent[7] = (((SWatch_PrevZCX->SWatch_Trig_ZCE[7] == POS_ZCSIG) !=
                 SWatch_U_Balarmset) && (SWatch_PrevZCX->SWatch_Trig_ZCE[7] !=
    UNINITIALIZED_ZCSIG));
  tmp = false;
  for (i = 0; i < 8; i++) {
    tmp = (tmp || zcEvent[i]);
  }

  if (tmp) {
    /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
     *  UnitDelay: '<S2>/Output'
     */
    /* Gateway: SWatch/SWatch */
    if ((int8_T)(zcEvent[0] ? SWatch_DW->Output_DSTATE != 0 ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) != 0) {
      /* Event: '<S3>:1' */
      SWatch_DW->sfEvent = SWatch_event_ptick;
      SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
        SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_Y_buzzer,
        SWatch_Y_isalarmset, SWatch_Y_submode, SWatch_DW);
    }

    /* Inport: '<Root>/Bplus' */
    if ((int8_T)(zcEvent[1] ? SWatch_U_Bplus ? RISING_ZCEVENT : FALLING_ZCEVENT :
                 NO_ZCEVENT) == 1) {
      /* Event: '<S3>:6' */
      SWatch_DW->sfEvent = SWatch_event_Bplus;
      SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
        SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_Y_buzzer,
        SWatch_Y_isalarmset, SWatch_Y_submode, SWatch_DW);
    }

    /* Inport: '<Root>/Bminus' */
    if ((int8_T)(zcEvent[2] ? SWatch_U_Bminus ? RISING_ZCEVENT : FALLING_ZCEVENT
                 : NO_ZCEVENT) == 1) {
      /* Event: '<S3>:7' */
      SWatch_DW->sfEvent = SWatch_event_Bminus;
      SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
        SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_Y_buzzer,
        SWatch_Y_isalarmset, SWatch_Y_submode, SWatch_DW);
    }

    /* Inport: '<Root>/Btime' */
    if ((int8_T)(zcEvent[3] ? SWatch_U_Btime ? RISING_ZCEVENT : FALLING_ZCEVENT :
                 NO_ZCEVENT) == 1) {
      /* Event: '<S3>:2' */
      SWatch_DW->sfEvent = SWatch_event_Btime;
      SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
        SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_Y_buzzer,
        SWatch_Y_isalarmset, SWatch_Y_submode, SWatch_DW);
    }

    /* Inport: '<Root>/Btimeset' */
    if ((int8_T)(zcEvent[4] ? SWatch_U_Btimeset ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      /* Event: '<S3>:3' */
      SWatch_DW->sfEvent = SWatch_event_Btimeset;
      SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
        SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_Y_buzzer,
        SWatch_Y_isalarmset, SWatch_Y_submode, SWatch_DW);
    }

    /* Inport: '<Root>/Balarm' */
    if ((int8_T)(zcEvent[5] ? SWatch_U_Balarm ? RISING_ZCEVENT : FALLING_ZCEVENT
                 : NO_ZCEVENT) == 1) {
      /* Event: '<S3>:4' */
      SWatch_DW->sfEvent = SWatch_event_Balarm;
      SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
        SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_Y_buzzer,
        SWatch_Y_isalarmset, SWatch_Y_submode, SWatch_DW);
    }

    /* Inport: '<Root>/Bswatch' */
    if ((int8_T)(zcEvent[6] ? SWatch_U_Bswatch ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      /* Event: '<S3>:5' */
      SWatch_DW->sfEvent = SWatch_event_Bstop;
      SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
        SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_Y_buzzer,
        SWatch_Y_isalarmset, SWatch_Y_submode, SWatch_DW);
    }

    /* Inport: '<Root>/Balarmset' */
    if ((int8_T)(zcEvent[7] ? SWatch_U_Balarmset ? RISING_ZCEVENT :
                 FALLING_ZCEVENT : NO_ZCEVENT) == 1) {
      /* Event: '<S3>:131' */
      SWatch_DW->sfEvent = SWatch_event_Balarmset;
      SWatch_chartstep_c3_SWatch(SWatch_Y_hours, SWatch_Y_minutes,
        SWatch_Y_seconds, SWatch_Y_tenths, SWatch_Y_mode, SWatch_Y_buzzer,
        SWatch_Y_isalarmset, SWatch_Y_submode, SWatch_DW);
    }
  }

  /* DataTypeConversion: '<S1>/Data Type Conversion' incorporates:
   *  UnitDelay: '<S2>/Output'
   */
  SWatch_PrevZCX->SWatch_Trig_ZCE[0] = (uint8_T)(SWatch_DW->Output_DSTATE != 0 ?
    (int32_T)POS_ZCSIG : (int32_T)ZERO_ZCSIG);

  /* Inport: '<Root>/Bplus' */
  SWatch_PrevZCX->SWatch_Trig_ZCE[1] = (uint8_T)(SWatch_U_Bplus ? (int32_T)
    POS_ZCSIG : (int32_T)ZERO_ZCSIG);

  /* Inport: '<Root>/Bminus' */
  SWatch_PrevZCX->SWatch_Trig_ZCE[2] = (uint8_T)(SWatch_U_Bminus ? (int32_T)
    POS_ZCSIG : (int32_T)ZERO_ZCSIG);

  /* Inport: '<Root>/Btime' */
  SWatch_PrevZCX->SWatch_Trig_ZCE[3] = (uint8_T)(SWatch_U_Btime ? (int32_T)
    POS_ZCSIG : (int32_T)ZERO_ZCSIG);

  /* Inport: '<Root>/Btimeset' */
  SWatch_PrevZCX->SWatch_Trig_ZCE[4] = (uint8_T)(SWatch_U_Btimeset ? (int32_T)
    POS_ZCSIG : (int32_T)ZERO_ZCSIG);

  /* Inport: '<Root>/Balarm' */
  SWatch_PrevZCX->SWatch_Trig_ZCE[5] = (uint8_T)(SWatch_U_Balarm ? (int32_T)
    POS_ZCSIG : (int32_T)ZERO_ZCSIG);

  /* Inport: '<Root>/Bswatch' */
  SWatch_PrevZCX->SWatch_Trig_ZCE[6] = (uint8_T)(SWatch_U_Bswatch ? (int32_T)
    POS_ZCSIG : (int32_T)ZERO_ZCSIG);

  /* Inport: '<Root>/Balarmset' */
  SWatch_PrevZCX->SWatch_Trig_ZCE[7] = (uint8_T)(SWatch_U_Balarmset ? (int32_T)
    POS_ZCSIG : (int32_T)ZERO_ZCSIG);

  /* Sum: '<S4>/FixPt Sum1' incorporates:
   *  Constant: '<S4>/FixPt Constant'
   *  UnitDelay: '<S2>/Output'
   */
  rtb_FixPtSum1 = (uint8_T)(SWatch_DW->Output_DSTATE + 1U);

  /* Switch: '<S5>/FixPt Switch' */
  if (rtb_FixPtSum1 > 1) {
    /* Update for UnitDelay: '<S2>/Output' incorporates:
     *  Constant: '<S5>/Constant'
     */
    SWatch_DW->Output_DSTATE = 0U;
  } else {
    /* Update for UnitDelay: '<S2>/Output' */
    SWatch_DW->Output_DSTATE = rtb_FixPtSum1;
  }

  /* End of Switch: '<S5>/FixPt Switch' */
}

/* Model initialize function */
void SWatch_initialize(RT_MODEL_SWatch_T *const SWatch_M, boolean_T
  *SWatch_U_Bplus, boolean_T *SWatch_U_Bminus, boolean_T *SWatch_U_Btime,
  boolean_T *SWatch_U_Btimeset, boolean_T *SWatch_U_Balarm, boolean_T
  *SWatch_U_Bswatch, boolean_T *SWatch_U_Balarmset, uint8_T *SWatch_Y_hours,
  uint8_T *SWatch_Y_minutes, uint8_T *SWatch_Y_seconds, uint8_T *SWatch_Y_tenths,
  uint8_T *SWatch_Y_mode, uint8_T *SWatch_Y_buzzer, boolean_T
  *SWatch_Y_isalarmset, uint8_T *SWatch_Y_submode)
{
  DW_SWatch_T *SWatch_DW = ((DW_SWatch_T *) SWatch_M->ModelData.dwork);
  PrevZCX_SWatch_T *SWatch_PrevZCX = ((PrevZCX_SWatch_T *)
    SWatch_M->ModelData.prevZCSigState);

  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)SWatch_DW, 0,
                sizeof(DW_SWatch_T));

  /* external inputs */
  (*SWatch_U_Bplus) = false;
  (*SWatch_U_Bminus) = false;
  (*SWatch_U_Btime) = false;
  (*SWatch_U_Btimeset) = false;
  (*SWatch_U_Balarm) = false;
  (*SWatch_U_Bswatch) = false;
  (*SWatch_U_Balarmset) = false;

  /* external outputs */
  (*SWatch_Y_hours) = 0U;
  (*SWatch_Y_minutes) = 0U;
  (*SWatch_Y_seconds) = 0U;
  (*SWatch_Y_tenths) = 0U;
  (*SWatch_Y_mode) = 0U;
  (*SWatch_Y_buzzer) = 0U;
  (*SWatch_Y_isalarmset) = false;
  (*SWatch_Y_submode) = 0U;

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      SWatch_PrevZCX->SWatch_Trig_ZCE[i] = UNINITIALIZED_ZCSIG;
    }

    /* InitializeConditions for Chart: '<S1>/SWatch' */
    SWatch_DW->is_alarmmode = SWatch_IN_NO_ACTIVE_CHILD;
    SWatch_DW->is_swatchmode = SWatch_IN_NO_ACTIVE_CHILD;
    SWatch_DW->was_swatchmode = SWatch_IN_NO_ACTIVE_CHILD;
    SWatch_DW->is_timesetmode = SWatch_IN_NO_ACTIVE_CHILD;

    /* Entry: SWatch/SWatch */
    /* Entry Internal: SWatch/SWatch */
    SWatch_DW->is_active_Control = 1U;

    /* Entry 'Control': '<S3>:13' */
    SWatch_DW->running = true;
    SWatch_DW->Srunning = false;

    /* InitializeConditions for Outport: '<Root>/buzzer' incorporates:
     *  InitializeConditions for Chart: '<S1>/SWatch'
     */
    *SWatch_Y_buzzer = 0U;

    /* InitializeConditions for Chart: '<S1>/SWatch' */
    /* Entry Internal 'Control': '<S3>:13' */
    /* Transition: '<S3>:24' */
    SWatch_DW->Ahours = 0U;
    SWatch_DW->Aminutes = 0U;
    SWatch_DW->is_Control = SWatch_IN_timemode;

    /* InitializeConditions for Outport: '<Root>/mode' incorporates:
     *  InitializeConditions for Chart: '<S1>/SWatch'
     */
    /* Entry 'timemode': '<S3>:22' */
    *SWatch_Y_mode = 0U;

    /* InitializeConditions for Chart: '<S1>/SWatch' */
    SWatch_DW->is_active_Timers = 1U;

    /* Entry Internal 'Timers': '<S3>:14' */
    SWatch_DW->is_active_Clock = 1U;

    /* Entry 'Clock': '<S3>:17' */
    SWatch_DW->hours = 0U;
    SWatch_DW->minutes = 0U;
    SWatch_DW->seconds = 0U;
    SWatch_DW->tenths = 0U;
    SWatch_DW->is_active_Stopwatch = 1U;

    /* Entry 'Stopwatch': '<S3>:239' */
    SWatch_DW->Shours = 0U;
    SWatch_DW->Sminutes = 0U;
    SWatch_DW->Sseconds = 0U;
    SWatch_DW->Stenths = 0U;
    SWatch_DW->is_active_AlarmMng = 1U;

    /* InitializeConditions for Outport: '<Root>/isalarmset' incorporates:
     *  InitializeConditions for Chart: '<S1>/SWatch'
     */
    /* Entry 'AlarmMng': '<S3>:15' */
    *SWatch_Y_isalarmset = false;

    /* InitializeConditions for Chart: '<S1>/SWatch' */
    /* Entry Internal 'AlarmMng': '<S3>:15' */
    /* Transition: '<S3>:123' */
    SWatch_DW->is_AlarmMng = SWatch_IN_check;
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
