GTEST_DIR =..
USER_DIR =.
CPPFLAGS +=-isystem $(GTEST_DIR)/include
CXXFLAGS +=-g -Wall -Wextra -pthread
TESTS =run_test
GTEST_HEADERS =$(GTEST_DIR)/include/*.h\
	       $(GTEST_DIR)/include/internal/*.h
FILES =$(foreach d,$(USER_DIR),$(wildcard $(d)/*.cpp))
OBJS =$(patsubst %.cpp,%.o,$(FILES))


all : $(TESTS)

clean :
	rm -f $(TESTS) gtest_main.a *.o

.PHONY :clean

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

%.o :%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


$(TESTS) : $(OBJS) gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
