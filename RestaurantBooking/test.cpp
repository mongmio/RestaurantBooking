#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "BookingScheduler.cpp"

TEST(BookingSchedulerTest, ������_���ÿ���_�����ϴ�_���ð�_�ƴѰ��_����Ұ�) {
	BookingScheduler bookingScheduler{ 10 };
	tm time{};
	time.tm_hour = 8;
	time.tm_min = 30;

	Customer customer{ "CUSTOMER_NAME", "+82-10-1234-4567" };
	Schedule schedule{ time, 2, customer };
	EXPECT_THROW(bookingScheduler.addSchedule(&schedule), std::exception);
}

TEST(BookingSchedulerTest, ������_���ÿ���_�����ϴ�_������_���_���డ��) {
	BookingScheduler bookingScheduler{ 10 };
	tm time{};
	time.tm_hour = 8;
	time.tm_min = 0;

	Customer customer{ "CUSTOMER_NAME", "+82-10-1234-4567" };
	Schedule schedule{ time, 2, customer };
	bookingScheduler.addSchedule(&schedule);
}

TEST(BookingSchedulerTest, �ð��뺰_�ο�������_�ִ�_����_�ð��뿡_Capacity_�ʰ���_���_���ܹ߻�) {
	BookingScheduler bookingScheduler{ 10 };
	tm time{};
	time.tm_hour = 8;
	time.tm_min = 0;

	Customer customer{ "CUSTOMER_NAME", "+82-10-1234-4567" };
	Schedule schedule1{ time, 10, customer };
	Schedule schedule2{ time, 1, customer };
	bookingScheduler.addSchedule(&schedule1);
	EXPECT_THROW(bookingScheduler.addSchedule(&schedule2), std::exception);
}

TEST(BookingSchedulerTest, �ð��뺰_�ο�������_�ִ�_����_�ð��밡_�ٸ���_Capacity_���־_������_�߰�_����) {

}

TEST(BookingSchedulerTest, ����Ϸ��_SMS��_������_�߼�) {

}

TEST(BookingSchedulerTest, �̸�����_����_��쿡��_�̸���_�̹߼�) {

}

TEST(BookingSchedulerTest, �̸�����_�ִ�_��쿡��_�̸���_�߼�) {

}

TEST(BookingSchedulerTest, ���糯¥��_�Ͽ�����_���_����Ұ�_����ó��) {

}

TEST(BookingSchedulerTest, ���糯¥��_�Ͽ�����_�ƴѰ��_���డ��) {

}