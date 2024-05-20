#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "BookingScheduler.cpp"

class BookingSchedulerTest : public testing::Test
{
protected:
	static constexpr int DEFAULT_CAPACITY = 10;
	BookingScheduler bookingScheduler{ DEFAULT_CAPACITY };

	tm createTm(int year, int mon, int day, int hour, int min)
	{
		return tm{ 0, min, hour, day, mon - 1, year - 1900, 0, 0, -1 };
	}

	Customer getDefaultCustomer(void)
	{
		return Customer{ "CUSTOMER_NAME", "+82-10-1234-4567" };
	}
};
TEST_F(BookingSchedulerTest, ������_���ÿ���_�����ϴ�_���ð�_�ƴѰ��_����Ұ�) {
	
	Schedule schedule{ createTm(2024, 5, 20, 8, 30), 2, getDefaultCustomer ()};
	EXPECT_THROW(bookingScheduler.addSchedule(&schedule), std::exception);
}

TEST_F(BookingSchedulerTest, ������_���ÿ���_�����ϴ�_������_���_���డ��) {
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer() };
	bookingScheduler.addSchedule(&schedule);
}

TEST_F(BookingSchedulerTest, �ð��뺰_�ο�������_�ִ�_����_�ð��뿡_Capacity_�ʰ���_���_���ܹ߻�) {
	Schedule schedule1{ createTm(2024, 5, 20, 8, 0), 10, getDefaultCustomer() };
	Schedule schedule2{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer() };
	bookingScheduler.addSchedule(&schedule1);
	EXPECT_THROW(bookingScheduler.addSchedule(&schedule2), std::exception);
}

TEST_F(BookingSchedulerTest, �ð��뺰_�ο�������_�ִ�_����_�ð��밡_�ٸ���_Capacity_���־_������_�߰�_����) {

}

TEST_F(BookingSchedulerTest, ����Ϸ��_SMS��_������_�߼�) {

}

TEST_F(BookingSchedulerTest, �̸�����_����_��쿡��_�̸���_�̹߼�) {

}

TEST_F(BookingSchedulerTest, �̸�����_�ִ�_��쿡��_�̸���_�߼�) {

}

TEST_F(BookingSchedulerTest, ���糯¥��_�Ͽ�����_���_����Ұ�_����ó��) {

}

TEST_F(BookingSchedulerTest, ���糯¥��_�Ͽ�����_�ƴѰ��_���డ��) {

}