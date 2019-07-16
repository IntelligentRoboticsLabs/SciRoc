#include "RP_fix_order.h"

/* The implementation of RP_fix_order.h */

/* constructor */
RP_fix_order::RP_fix_order(ros::NodeHandle &nh)
: nh_(nh),
  Action("fix_order"),
  robot_id()
{

}

void RP_fix_order::activateCode()
{
  for (size_t i = 0; i < last_msg_.parameters.size(); i++)
  {
    ROS_INFO("Param %s = %s",
      last_msg_.parameters[i].key.c_str(),
      last_msg_.parameters[i].value.c_str());
    if (0 == last_msg_.parameters[i].key.compare("r"))
      robot_id = last_msg_.parameters[i].value;
  }

  std::list<bica_graph::StringEdge> edges_list =  graph_.get_string_edges();
  for (auto it = edges_list.begin(); it != edges_list.end(); ++it)
  {
    std::string edge = it->get();
    if (edge.find("needs") != std::string::npos)
      object_needed = it->get_target();
  }
  graph_.add_edge(
    robot_id,
    "say: Excuse me sir, I can't find the " + object_needed + ". Could you bring me it?",
    "barman");
  setSuccess();
}

void RP_fix_order::deActivateCode(){}

/*-------------*/
/* Main method */
/*-------------*/

int main(int argc, char **argv) {

    ros::init(argc, argv, "rosplan_interface_fix_order");
    ros::NodeHandle nh("~");

    // create PDDL action subscriber
    RP_fix_order rpmb(nh);

    // listen for action dispatch
    ros::Subscriber ds = nh.subscribe("/kcl_rosplan/action_dispatch", 1000, &KCL_rosplan::RPActionInterface::dispatchCallback, dynamic_cast<KCL_rosplan::RPActionInterface*>(&rpmb));
    rpmb.runActionInterface();

    return 0;
}