// Generated by gencpp from file service_client_test/intsumRequest.msg
// DO NOT EDIT!


#ifndef SERVICE_CLIENT_TEST_MESSAGE_INTSUMREQUEST_H
#define SERVICE_CLIENT_TEST_MESSAGE_INTSUMREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace service_client_test
{
template <class ContainerAllocator>
struct intsumRequest_
{
  typedef intsumRequest_<ContainerAllocator> Type;

  intsumRequest_()
    : num1(0)
    , num2(0)  {
    }
  intsumRequest_(const ContainerAllocator& _alloc)
    : num1(0)
    , num2(0)  {
  (void)_alloc;
    }



   typedef int32_t _num1_type;
  _num1_type num1;

   typedef int32_t _num2_type;
  _num2_type num2;





  typedef boost::shared_ptr< ::service_client_test::intsumRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::service_client_test::intsumRequest_<ContainerAllocator> const> ConstPtr;

}; // struct intsumRequest_

typedef ::service_client_test::intsumRequest_<std::allocator<void> > intsumRequest;

typedef boost::shared_ptr< ::service_client_test::intsumRequest > intsumRequestPtr;
typedef boost::shared_ptr< ::service_client_test::intsumRequest const> intsumRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::service_client_test::intsumRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::service_client_test::intsumRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::service_client_test::intsumRequest_<ContainerAllocator1> & lhs, const ::service_client_test::intsumRequest_<ContainerAllocator2> & rhs)
{
  return lhs.num1 == rhs.num1 &&
    lhs.num2 == rhs.num2;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::service_client_test::intsumRequest_<ContainerAllocator1> & lhs, const ::service_client_test::intsumRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace service_client_test

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::service_client_test::intsumRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::service_client_test::intsumRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::service_client_test::intsumRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::service_client_test::intsumRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::service_client_test::intsumRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::service_client_test::intsumRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::service_client_test::intsumRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c68f3979e1a90aac7d1c75a1096d1e60";
  }

  static const char* value(const ::service_client_test::intsumRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc68f3979e1a90aacULL;
  static const uint64_t static_value2 = 0x7d1c75a1096d1e60ULL;
};

template<class ContainerAllocator>
struct DataType< ::service_client_test::intsumRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "service_client_test/intsumRequest";
  }

  static const char* value(const ::service_client_test::intsumRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::service_client_test::intsumRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# 请求\n"
"int32 num1\n"
"int32 num2\n"
;
  }

  static const char* value(const ::service_client_test::intsumRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::service_client_test::intsumRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.num1);
      stream.next(m.num2);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct intsumRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::service_client_test::intsumRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::service_client_test::intsumRequest_<ContainerAllocator>& v)
  {
    s << indent << "num1: ";
    Printer<int32_t>::stream(s, indent + "  ", v.num1);
    s << indent << "num2: ";
    Printer<int32_t>::stream(s, indent + "  ", v.num2);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SERVICE_CLIENT_TEST_MESSAGE_INTSUMREQUEST_H
