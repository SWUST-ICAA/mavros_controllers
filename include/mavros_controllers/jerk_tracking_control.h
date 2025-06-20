/****************************************************************************
 *
 *   Copyright (c) 2025 Nanwan. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @brief Jerk tracking controller implementation
 *
 * This class implements a controller that tracks desired jerk trajectories
 * for quadrotor control. It inherits from the Control base class and
 * provides specific implementation for jerk-based tracking control.
 *
 * @author Nanwan <nanwan2004@126.com>
 */

#ifndef JERK_TRACKING_CONTROL_H
#define JERK_TRACKING_CONTROL_H

#include "mavros_controllers/common.h"
#include "mavros_controllers/control.h"

class JerkTrackingControl : public Control {
 public:
  /**
   * @brief Constructor
   */
  JerkTrackingControl();

  /**
   * @brief Destructor
   */
  virtual ~JerkTrackingControl();

  /**
   * @brief Updates the jerk tracking controller state
   * 
   * Implements a jerk tracking control algorithm that considers
   * the rate of change of acceleration for more precise trajectory
   * tracking.
   *
   * @param curr_att Current attitude quaternion [w,x,y,z]
   * @param ref_att Reference attitude quaternion [w,x,y,z]
   * @param ref_acc Reference acceleration vector [m/s^2]
   * @param ref_jerk Reference jerk vector [m/s^3]
   */
  void Update(Eigen::Vector4d &curr_att,
              const Eigen::Vector4d &ref_att,
              const Eigen::Vector3d &ref_acc,
              const Eigen::Vector3d &ref_jerk) override;

 private:
  Eigen::Vector3d last_ref_acc_{Eigen::Vector3d::Zero()};  ///< Last reference acceleration for jerk computation
};

#endif
