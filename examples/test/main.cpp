#include "nano/utest.h"

struct test_case {
  test_case()
      : success_count(0)
      , count(0) {}

  std::size_t success_count;
  std::size_t count;
  std::string desc;
};

struct test_group {
  std::map<std::string, test_case> tests;
};

void xml_formatter(std::ostream& stream, const std::vector<nano::test::check_result>& results);
void dump(std::ostream& stream, const std::vector<nano::test::check_result>& results);

namespace {
TEST_CASE("Foo", FooA, "Foo A") { EXPECT_EQ(1, 1); }

TEST_CASE("Foo", FooB, "Foo B") { EXPECT_EQ(1, 1); }

TEST_CASE("Foo", FooC, "Foo C") { EXPECT_EQ(1, 1); }

TEST_CASE("Bar", BarA, "Bar A") { EXPECT_EQ(1, 1); }

TEST_CASE("Bar", BarB, "Bar B") { EXPECT_EQ(1, 1); }

TEST_CASE("Bar", BarC, "Bar C") {
  EXPECT_EQ(1, 1);
  EXPECT_EQ(2, 2);
}
} // namespace.

void xml_formatter(std::ostream& stream, const std::vector<nano::test::check_result>& results) {
  std::map<std::string, test_group> groups;

  for (std::size_t i = 0; i < results.size(); i++) {
    const nano::test::check_result& r = results[i];
    test_case& tc = groups[r.group].tests[r.item->name];
    tc.success_count += r.success;
    tc.count++;
    tc.desc = r.item->desc;
  }

  typedef std::map<std::string, test_group>::const_iterator group_iterator;
  typedef std::map<std::string, test_case>::const_iterator test_iterator;

  stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
  stream << "<tests>" << std::endl;

#ifdef NANO_TEST_CPP_98
  for (group_iterator group = groups.begin(); group != groups.end(); ++group)
#else
  for (group_iterator group = groups.cbegin(); group != groups.cend(); ++group)
#endif
  {
    stream << "  <group>" << std::endl;
    stream << "    <name>" << group->first << "</name>" << std::endl;

    stream << "    <cases>" << std::endl;
    const std::map<std::string, test_case>& test_map = group->second.tests;

#ifdef NANO_TEST_CPP_98
    for (test_iterator tcases = test_map.begin(); tcases != test_map.end(); ++tcases)
#else
    for (test_iterator tcases = test_map.cbegin(); tcases != test_map.cend(); ++tcases)
#endif
    {
      stream << "      <test>" << std::endl;
      stream << "        <name>" << tcases->first << "</name>" << std::endl;
      stream << "        <success>" << tcases->second.success_count << "</success>" << std::endl;
      stream << "        <count>" << tcases->second.count << "</count>" << std::endl;
      stream << "        <desc>" << tcases->second.desc << "</desc>" << std::endl;
      stream << "      </test>" << std::endl;
    }

    stream << "    </cases>" << std::endl;
    stream << "  </group>" << std::endl;
  }

  stream << "</tests>" << std::endl;
}

void dump(std::ostream& stream, const std::vector<nano::test::check_result>& results) {
  for (std::size_t i = 0; i < results.size(); i++) {
    const nano::test::check_result& r = results[i];
    stream << "[ " << i << " ]" << std::endl;
    stream << "  item.name  : " << r.item->name << std::endl;
    stream << "  item.desc  : " << r.item->desc << std::endl;
    stream << "  item.flags : " << r.item->flags << std::endl;
    stream << "  group      : " << r.group << std::endl;
    stream << "  expr       : " << r.expr << std::endl;
    stream << "  file       : " << r.file << std::endl;
    stream << "  line       : " << r.line << std::endl;
    stream << "  end_time   : " << r.end_time << std::endl;
    stream << "  success    : " << r.success << std::endl << std::endl;
  }
}

int main(int argc, const char* argv[]) {
  std::vector<nano::test::check_result> check_results;
  int result = nano::test::run(argc, argv, check_results);

  std::cout << "----------------------------------" << std::endl;
  std::cout << "XML" << std::endl;
  std::cout << "----------------------------------" << std::endl;
  xml_formatter(std::cout, check_results);

  std::cout << "----------------------------------" << std::endl;
  std::cout << "DUMP" << std::endl;
  std::cout << "----------------------------------" << std::endl;
  check_results.clear();
  result = nano::test::run(argc, argv, check_results);
  xml_formatter(std::cout, check_results);

  //  dump(std::cout, check_results);

  return result;
}
