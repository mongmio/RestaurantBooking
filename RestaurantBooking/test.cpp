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
TEST_F(BookingSchedulerTest, 예약은_정시에만_가능하다_정시가_아닌경우_예약불가) {
	
	Schedule schedule{ createTm(2024, 5, 20, 8, 30), 2, getDefaultCustomer ()};
	EXPECT_THROW(bookingScheduler->addSchedule(&schedule), std::exception);
}

TEST_F(BookingSchedulerTest, 예약은_정시에만_가능하다_정시인_경우_예약가능) {
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer() };
	bookingScheduler->addSchedule(&schedule);
}

TEST_F(BookingSchedulerTest, 시간대별_인원제한이_있다_같은_시간대에_Capacity_초과할_경우_예외발생) {
	Schedule schedule1{ createTm(2024, 5, 20, 8, 0), 10, getDefaultCustomer() };
	Schedule schedule2{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer() };
	bookingScheduler->addSchedule(&schedule1);
	EXPECT_THROW(bookingScheduler->addSchedule(&schedule2), std::exception);
}

TEST_F(BookingSchedulerTest, 시간대별_인원제한이_있다_같은_시간대가_다르면_Capacity_차있어도_스케쥴_추가_성공) {
	Schedule schedule1{ createTm(2024, 5, 20, 8, 0), 10, getDefaultCustomer() };
	Schedule schedule2{ createTm(2024, 5, 20, 9, 0), 2, getDefaultCustomer() };
	bookingScheduler->addSchedule(&schedule1);
	bookingScheduler->addSchedule(&schedule2);
}

TEST_F(BookingSchedulerTest, 예약완료시_SMS는_무조건_발송) {
	EXPECT_CALL(smsSenderMock, send(testing::_)).Times(1);
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer() };
	bookingScheduler->addSchedule(&schedule);
}

TEST_F(BookingSchedulerTest, 이메일이_없는_경우에는_이메일_미발송) {
	EXPECT_CALL(mailSenderMock, sendMail(testing::_)).Times(0);
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer(true) };
	bookingScheduler->addSchedule(&schedule);
}

TEST_F(BookingSchedulerTest, 이메일이_있는_경우에는_이메일_발송) {
	EXPECT_CALL(mailSenderMock, sendMail(testing::_)).Times(1);
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer(false) };
	bookingScheduler->addSchedule(&schedule);
}

TEST_F(BookingSchedulerTest, 현재날짜가_일요일인_경우_예약불가_예외처리) {
	setCurrentDayOfWeek("Sunday");
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer(false) };
	EXPECT_THROW(bookingScheduler->addSchedule(&schedule), std::exception);
}

TEST_F(BookingSchedulerTest, 현재날짜가_일요일이_아닌경우_예약가능) {
	setCurrentDayOfWeek("Mocday");
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer(false) };
	bookingScheduler->addSchedule(&schedule);
}