#include <iostream>
#include "addressbook.pb.h"

int main(int argc, const char* argv[])
{
    addressbook::AddressBook person;
    addressbook::Person* pi = person.add_person_info();

    pi->set_name("aut");
    pi->set_id(1219);
    std::cout << "before clear(), id = " << pi->id() << std::endl;
    pi->clear_id();
    std::cout << "after  clear(), id = " << pi->id() << std::endl;
    pi->set_id(1087);
    if (!pi->has_email())
        pi->set_email("autyinjing@126.com");

    addressbook::Person::PhoneNumber* pn = pi->add_phone();
    pn->set_number("021-8888-8888");
    pn = pi->add_phone();
    pn->set_number("138-8888-8888");
    pn->set_type(addressbook::Person::MOBILE);

    uint32_t size = person.ByteSize();
    unsigned char byteArray[size];
    person.SerializeToArray(byteArray, size);

    addressbook::AddressBook help_person;
    help_person.ParseFromArray(byteArray, size);
    addressbook::Person help_pi = help_person.person_info(0);

    std::cout << "*****************************" << std::endl;
    std::cout << "id:    " << help_pi.id() << std::endl;
    std::cout << "name:  " << help_pi.name() << std::endl;
    std::cout << "email: " << help_pi.email() << std::endl;

    for (int i = 0; i < help_pi.phone_size(); ++i)
    {
        auto help_pn = help_pi.mutable_phone(i);
        std::cout << "phone_type: " << help_pn->type() << std::endl;
        std::cout << "phone_number: " << help_pn->number() << std::endl;
    }
    std::cout << "*****************************" << std::endl;

    return 0;
}
