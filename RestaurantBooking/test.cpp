#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "BookingScheduler.cpp"
#include <iostream>

class SmsSenderGMock : public SmsSender
{
public:
	MOCK_METHOD(void, send, (Schedule*), (override));
};

class MailSenderGMock : public MailSender
{
public:
	MOCK_METHOD(void, sendMail, (Schedule*), (override));
};

class TestableBookingScheduler : public BookingScheduler
{
public:
	TestableBookingScheduler(int capacityPerHour, SmsSender* _smsSender, MailSender* _mailSender) :
		BookingScheduler(capacityPerHour, _smsSender, _mailSender) {}
	MOCK_METHOD(string, getDayOfWeek, (time_t), (override));
};

class BookingSchedulerTest : public testing::Test
{
protected:
	testing::NiceMock<SmsSenderGMock> smsSenderMock{};
	testing::NiceMock<MailSenderGMock> mailSenderMock{};
	static constexpr int DEFAULT_CAPACITY = 10;
	BookingScheduler* bookingScheduler{};
	BookingScheduler originalScheduler{ DEFAULT_CAPACITY, &smsSenderMock, &mailSenderMock };
	testing::NiceMock<TestableBookingScheduler> schedulerMock{ DEFAULT_CAPACITY, &smsSenderMock, &mailSenderMock };
	void SetUp(void) override
	{
		bookingScheduler = &originalScheduler;
	}
	tm createTm(int year, int mon, int day, int hour, int min)
	{
		return tm{ 0, min, hour, day, mon - 1, year - 1900, 0, 0, -1 };
	}

	Customer getDefaultCustomer(bool noEmail = false)
	{
		if (noEmail)
		{
			return Customer{ "CUSTOMER_NAME", "+82-10-1234-4567" };
		}
		return Customer{ "CUSTOMER_NAME", "+82-10-1234-4567" , "test@test.com"};
	}

	void setCurrentDayOfWeek(const string dayOfWeek)
	{
		EXPECT_CALL(schedulerMock, getDayOfWeek(testing::_)).WillRepeatedly(testing::Return(dayOfWeek));
		bookingScheduler = &schedulerMock;
	}
};
TEST_F(BookingSchedulerTest, ������_���ÿ���_�����ϴ�_���ð�_�ƴѰ��_����Ұ�) {
	
	Schedule schedule{ createTm(2024, 5, 20, 8, 30), 2, getDefaultCustomer ()};
	EXPECT_THROW(bookingScheduler->addSchedule(&schedule), std::exception);
}

TEST_F(BookingSchedulerTest, ������_���ÿ���_�����ϴ�_������_���_���డ��) {
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer() };
	bookingScheduler->addSchedule(&schedule);
}

TEST_F(BookingSchedulerTest, �ð��뺰_�ο�������_�ִ�_����_�ð��뿡_Capacity_�ʰ���_���_���ܹ߻�) {
	Schedule schedule1{ createTm(2024, 5, 20, 8, 0), 10, getDefaultCustomer() };
	Schedule schedule2{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer() };
	bookingScheduler->addSchedule(&schedule1);
	EXPECT_THROW(bookingScheduler->addSchedule(&schedule2), std::exception);
}

TEST_F(BookingSchedulerTest, �ð��뺰_�ο�������_�ִ�_����_�ð��밡_�ٸ���_Capacity_���־_������_�߰�_����) {
	Schedule schedule1{ createTm(2024, 5, 20, 8, 0), 10, getDefaultCustomer() };
	Schedule schedule2{ createTm(2024, 5, 20, 9, 0), 2, getDefaultCustomer() };
	bookingScheduler->addSchedule(&schedule1);
	bookingScheduler->addSchedule(&schedule2);
}

TEST_F(BookingSchedulerTest, ����Ϸ��_SMS��_������_�߼�) {
	EXPECT_CALL(smsSenderMock, send(testing::_)).Times(1);
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer() };
	bookingScheduler->addSchedule(&schedule);
}

TEST_F(BookingSchedulerTest, �̸�����_����_��쿡��_�̸���_�̹߼�) {
	EXPECT_CALL(mailSenderMock, sendMail(testing::_)).Times(0);
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer(true) };
	bookingScheduler->addSchedule(&schedule);
}

TEST_F(BookingSchedulerTest, �̸�����_�ִ�_��쿡��_�̸���_�߼�) {
	EXPECT_CALL(mailSenderMock, sendMail(testing::_)).Times(1);
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer(false) };
	bookingScheduler->addSchedule(&schedule);
}

TEST_F(BookingSchedulerTest, ���糯¥��_�Ͽ�����_���_����Ұ�_����ó��) {
	setCurrentDayOfWeek("Sunday");
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer(false) };
	EXPECT_THROW(bookingScheduler->addSchedule(&schedule), std::exception);
}

TEST_F(BookingSchedulerTest, ���糯¥��_�Ͽ�����_�ƴѰ��_���డ��) {
	setCurrentDayOfWeek("Mocday");
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer(false) };
	bookingScheduler->addSchedule(&schedule);
}