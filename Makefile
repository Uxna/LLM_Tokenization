all: main.cpp Dictionary_class.hpp Slot_class.hpp Word_class.hpp
	g++ -g -std=c++11 main.cpp Dictionary_class.hpp Slot_class.hpp Word_class.hpp