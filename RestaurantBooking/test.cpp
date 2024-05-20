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
TEST_F(BookingSchedulerTest, 예약은_정시에만_가능하다_정시가_아닌경우_예약불가) {
	
	Schedule schedule{ createTm(2024, 5, 20, 8, 30), 2, getDefaultCustomer ()};
	EXPECT_THROW(bookingScheduler.addSchedule(&schedule), std::exception);
}

TEST_F(BookingSchedulerTest, 예약은_정시에만_가능하다_정시인_경우_예약가능) {
	Schedule schedule{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer() };
	bookingScheduler.addSchedule(&schedule);
}

TEST_F(BookingSchedulerTest, 시간대별_인원제한이_있다_같은_시간대에_Capacity_초과할_경우_예외발생) {
	Schedule schedule1{ createTm(2024, 5, 20, 8, 0), 10, getDefaultCustomer() };
	Schedule schedule2{ createTm(2024, 5, 20, 8, 0), 2, getDefaultCustomer() };
	bookingScheduler.addSchedule(&schedule1);
	EXPECT_THROW(bookingScheduler.addSchedule(&schedule2), std::exception);
}

TEST_F(BookingSchedulerTest, 시간대별_인원제한이_있다_같은_시간대가_다르면_Capacity_차있어도_스케쥴_추가_성공) {

}

TEST_F(BookingSchedulerTest, 예약완료시_SMS는_무조건_발송) {

}

TEST_F(BookingSchedulerTest, 이메일이_없는_경우에는_이메일_미발송) {

}

TEST_F(BookingSchedulerTest, 이메일이_있는_경우에는_이메일_발송) {

}

TEST_F(BookingSchedulerTest, 현재날짜가_일요일인_경우_예약불가_예외처리) {

}

TEST_F(BookingSchedulerTest, 현재날짜가_일요일이_아닌경우_예약가능) {

}