cmake_minimum_required(VERSION 3.7)
project(unemployed_morrons)

find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

include_directories(include)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/Monitor.cpp src/Monitor.h tests/tests.cpp src/Packet.h src/Message.cpp src/Message.h src/Serializer.cpp src/Serializer.h src/Messenger.cpp src/Messenger.h src/Packet.cpp src/DerivedMessage.cpp src/DerivedMessage.h src/Configuration.h src/Configuration.cpp src/RequestCompanyMessage.cpp src/RequestCompanyMessage.h src/ReplyCompanyMessage.cpp src/ReplyCompanyMessage.h src/AgentInterface.cpp src/AgentInterface.h src/Agent.cpp src/Agent.h src/Company.cpp src/Company.h src/AgentRequest.cpp src/AgentRequest.h tests/testCompany.cpp src/RequestsQueue.cpp src/RequestsQueue.h tests/testRequestsQueue.cpp tests/testAutoMessaging.cpp tests/testAgent.cpp src/GoOutOfQueueMessage.cpp src/GoOutOfQueueMessage.h)
add_executable(unemployed_morrons ${SOURCE_FILES})

target_link_libraries(unemployed_morrons ${MPI_LIBRARIES})

if (MPI_COMPILE_FLAGS)
    message("ASD")
    set_target_properties(unemployed_morrons PROPERTIES
            COMPILE_FLAGS "MPI_COMPILE_FLAGS")
endif ()

if (MPI_LINK_FLAGS)
    set_target_properties(unemployed_morrons PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif ()