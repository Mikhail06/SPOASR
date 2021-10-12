#include "ros/ros.h" 				//Файл в котором описаны базывые команды, функции классы ROS
#include "geometry_msgs/Twist.h"	//Файл в котором прописан класс того сообщения, которое мы будем публиковать в топик /turtle1/cmd_vel

int main(int argc, char **argv)
{							// ↓ - имя ноды по умолчанию
	ros::init(argc, argv, "publisher"); //init инициализирует основные процессы ROS перед тем как нода должна начать работать
	ros::NodeHandle n;					//Создается объект класса ros::NodeHandle, с помощью которого мы будем управлять всей нашей нодой
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000); //Создание объекта типа ros::Publisher, с помощью которого будет осуществлятся отправка сообщений в топики
	
	ros::Rate loop_rate(1); 		//Объект класса ros::Rate, который устонавливает скорость собщений в топик в секунду
	for (int t=0; t<30; t++){ 		//20 - это количество итераций
		geometry_msgs::Twist pos;	//Экземпляр типа geometry_msgs:: - Одно сообщение
		pos.linear.x=1;						//Движение вперёд
		pos.angular.z=std::abs(3*cos(0.2*t));	//Угол поворота
		
		ROS_INFO(	"Move to position:\n"		//Команда выводит на экран приведенное сообщение
					"1) pos.linear: x=%f y=%f z=%f\n"
					"2) pos.angular: x=%f y=%f z=%f\n",
					pos.linear.x, pos.linear.y, pos.linear.z,
					pos.angular.x, pos.angular.y, pos.angular.z);
		pub.publish(pos); 	//Отправляется сообщение
		loop_rate.sleep();	//Ждём для того, чтобы сохранить скорость loop_rate
	}
	ros::spinOnce();	//
	return 0;
}