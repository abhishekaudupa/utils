# Directories.
thisdir = $(abspath .)/
includedir = $(thisdir)include/
srcdir = $(thisdir)src/
bindir = $(thisdir)bin/
builddir = $(thisdir)build/
testsrcdir = $(thisdir)test/src/
testbindir = $(thisdir)test/bin/
testbuilddir = $(thisdir)test/build/
covdir = $(thisdir)/coverage/

# Build reports.
covreport = $(covdir)coverage_report.txt
testreport = $(covdir)test_report.txt
memleakreport = $(covdir)memory_leak_report.txt

# Compiler settings.
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c99 -iquote $(includedir)
CXX = g++
COVFLAGS = -fprofile-arcs -ftest-coverage --coverage -Og
CXXFLAGS = -Wall -Werror -Wextra -iquote $(includedir)
VALG = valgrind
VALGFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$(memleakreport)

# Program objects.
modclient = $(bindir)modclient
modserver = $(bindir)modserver
test = $(testbindir)test
modcommonobjs = modbus_pdu.o
modclientobjs = $(modcommonobjs) modclient.o
modserverobjs = $(modcommonobjs) modserver.o
testobjs = test_modbus_pdu.o test_main.o

#all: $(all_with_test)

all_with_test: $(test) $(modclient) $(modserver)

$(modserver): $(addprefix $(builddir), $(modserverobjs)) \
	| $(bindir)
	@echo building server simulator executable $(notdir $@)
	@$(CC) $^ -o $@

$(modclient): $(addprefix $(builddir), $(modclientobjs)) \
	| $(bindir)
	@echo building client simulator executable $(notdir $@)
	@$(CC) $^ -o $@

$(builddir)%.o: $(srcdir)%.c $(includedir)%.h | $(builddir)
	@echo building object $(notdir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(builddir)%.o: $(srcdir)%.c | $(builddir)
	@echo building object $(notdir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(test): $(addprefix $(testbuilddir), $(testobjs)) \
	$(addprefix $(testbuilddir)c_, $(filter-out $(modclient) $(modserver), $(modcommonobjs))) \
	| $(testbindir) $(covdir)
	@echo building test executable $(notdir $@)
	@$(CXX) $^ -lgtest -pthread -lgcov -o $@
	@echo Running tests...
	@rm -rf $(testbuilddir)*.gcda
	@$(VALG) $(VALGFLAGS) $@ > $(testreport) || { echo "Test/s Failed" && rm -rf $(testbindir) && false; }
	@echo Tests successful
	@echo Checking code coverage...
	@gcov $(testbuilddir)c_*.gcda > $(covreport)
	@mv *.gcov $(covdir)
	@echo Code coverage check complete.

$(testbuilddir)%.o: $(testsrcdir)%.cpp | $(testbuilddir)
	@echo building test object $(notdir $@)
	@$(CXX) $(CXXFLAGS) $(COVFLAGS) -c $< -o $@

$(testbuilddir)c_%.o: $(srcdir)%.c $(includedir)%.h | $(testbuilddir)
	@echo building test object $(notdir $@)
	@$(CC) $(CFLAGS) $(COVFLAGS) -c $< -o $@

$(bindir):
	@mkdir -p $@

$(builddir):
	@mkdir -p $@

$(testbindir):
	@mkdir -p $@

$(testbuilddir):
	@mkdir -p $@

$(covdir):
	@mkdir -p $@

view_test_report:
	@vi $(testreport)

view_test_report_short:
	@echo "|----------------------|"
	@echo "|     Test report      |"
	@echo "|----------------------|"
	@cat $(testreport) | tail -3
	@echo "View the test report for detailed analysis"
	@echo

view_coverage_report:
	@echo "|----------------------|"
	@echo "| Code coverage report |"
	@echo "|----------------------|"
	@cat $(covreport)
	@echo "View the coverage report for detailed analysis"
	@echo

view_memory_leak_report:
	@echo "|----------------------|"
	@echo "| Memory check report  |"
	@echo "|----------------------|"
	@cat $(memleakreport)
	@echo

clean:
	@rm -rf $(bindir) $(builddir) $(testbindir) $(testbuilddir) $(covdir)
	@clear

run_client: $(modclient)
	@$(modclient)

.PHONY: clean all all_with_test
