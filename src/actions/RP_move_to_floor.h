/*********************************************************************
*  Software License Agreement (BSD License)
*
*   Copyright (c) 2018, Intelligent Robotics
*   All rights reserved.
*
*   Redistribution and use in source and binary forms, with or without
*   modification, are permitted provided that the following conditions
*   are met:

*    * Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*    * Redistributions in binary form must reproduce the above
*      copyright notice, this list of conditions and the following
*      disclaimer in the documentation and/or other materials provided
*      with the distribution.
*    * Neither the name of Intelligent Robotics nor the names of its
*      contributors may be used to endorse or promote products derived
*      from this software without specific prior written permission.

*   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*   COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*   POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Jonatan Gines jonatan.gines@urjc.es */

/* Mantainer: Jonatan Gines jonatan.gines@urjc.es */

#include <ros/ros.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <boost/foreach.hpp>

#include <bica_planning/Action.h>
#include <bica_graph/graph_client.h>
#include <sensor_msgs/LaserScan.h>


#ifndef KCL_move_to_floor
#define KCL_move_to_floor


class RP_move_to_floor : public bica_planning::Action
{
public:
  explicit RP_move_to_floor(ros::NodeHandle& nh);

protected:
  void activateCode();
  void deActivateCode();
  void step();
  void timeoutCB(const ros::TimerEvent&);
  void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan);

private:

  ros::NodeHandle nh_;
  bica_graph::GraphClient graph_;
  enum StateType
  {
    INIT,
    CHECKING_DOOR,
    ASK_FLOOR,
    END
  };
  StateType state_;
  ros::Timer init_timer_;
  sensor_msgs::LaserScan scan_;
  ros::Subscriber scan_sub_;
  std::string robot_id_;
  std::string target_floor_;
};

#endif