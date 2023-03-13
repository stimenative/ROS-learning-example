#!/usr/bin/env python3

import rospy
from service_client_test.srv import intsum,intsumRequest,intsumResponse

if __name__ == "__main__":
    # initialize
    rospy.init_node("insum_client")
    # create client object
    client = rospy.ServiceProxy("intsum",intsum)
    # organize & send data
    response = client.call(12,14)
    # handle response
    rospy.loginfo("response data is : %d",response.sum)