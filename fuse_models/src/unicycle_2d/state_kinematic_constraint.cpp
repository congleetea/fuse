/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2018, Locus Robotics
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */
#include <fuse_models/unicycle_2d/state_kinematic_constraint.h>
#include <fuse_models/unicycle_2d/state_cost_functor.h>

#include <ceres/autodiff_cost_function.h>
#include <Eigen/Dense>
#include <fuse_variables/acceleration_linear_2d_stamped.h>
#include <fuse_variables/orientation_2d_stamped.h>
#include <fuse_variables/position_2d_stamped.h>
#include <fuse_variables/velocity_angular_2d_stamped.h>
#include <fuse_variables/velocity_linear_2d_stamped.h>

#include <ostream>


namespace fuse_models
{

namespace unicycle_2d
{

StateKinematicConstraint::StateKinematicConstraint(
  const fuse_variables::Position2DStamped& position1,
  const fuse_variables::Orientation2DStamped& yaw1,
  const fuse_variables::VelocityLinear2DStamped& linear_velocity1,
  const fuse_variables::VelocityAngular2DStamped& yaw_velocity1,
  const fuse_variables::AccelerationLinear2DStamped& linear_acceleration1,
  const fuse_variables::Position2DStamped& position2,
  const fuse_variables::Orientation2DStamped& yaw2,
  const fuse_variables::VelocityLinear2DStamped& linear_velocity2,
  const fuse_variables::VelocityAngular2DStamped& yaw_velocity2,
  const fuse_variables::AccelerationLinear2DStamped& linear_acceleration2,
  const fuse_core::Matrix8d& covariance) :
    fuse_core::Constraint{  // NOLINT
      position1.uuid(),
      yaw1.uuid(),
      linear_velocity1.uuid(),
      yaw_velocity1.uuid(),
      linear_acceleration1.uuid(),
      position2.uuid(),
      yaw2.uuid(),
      linear_velocity2.uuid(),
      yaw_velocity2.uuid(),
      linear_acceleration2.uuid()},  // NOLINT
    dt_((position2.stamp() - position1.stamp()).toSec()),
    sqrt_information_(covariance.inverse().llt().matrixU())
{
}

void StateKinematicConstraint::print(std::ostream& stream) const
{
  stream << type() << "\n"
         << "  uuid: " << uuid() << "\n"
         << "  position variable 1: " << variables_.at(0) << "\n"
         << "  yaw variable 1: " << variables_.at(1) << "\n"
         << "  linear velocity variable 1: " << variables_.at(2) << "\n"
         << "  yaw velocity variable 1: " << variables_.at(3) << "\n"
         << "  linear acceleration variable 1: " << variables_.at(4) << "\n"
         << "  position variable 2: " << variables_.at(5) << "\n"
         << "  yaw variable 2: " << variables_.at(6) << "\n"
         << "  linear velocity variable 2: " << variables_.at(7) << "\n"
         << "  yaw velocity variable 2: " << variables_.at(8) << "\n"
         << "  linear acceleration variable 2: " << variables_.at(9) << "\n"
         << "  dt: " << dt_ << "\n"
         << "  sqrt_info: " << sqrtInformation() << "\n";
}

ceres::CostFunction* StateKinematicConstraint::costFunction() const
{
  return new ceres::AutoDiffCostFunction<StateCostFunctor, 8, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2>(
    new StateCostFunctor(dt_, sqrt_information_));
}

}  // namespace unicycle_2d

}  // namespace fuse_models