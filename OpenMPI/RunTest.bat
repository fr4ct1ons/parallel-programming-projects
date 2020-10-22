echo "Starting tests."

echo "Running serial on smallest case 5 times."
TestingProject_SRL.exe 720000000
TestingProject_SRL.exe 720000000
TestingProject_SRL.exe 720000000
TestingProject_SRL.exe 720000000
TestingProject_SRL.exe 720000000

echo "Running serial on worst case 5 times."
									
TestingProject_SRL.exe 1400000000
TestingProject_SRL.exe 1400000000
TestingProject_SRL.exe 1400000000
TestingProject_SRL.exe 1400000000
TestingProject_SRL.exe 1400000000

echo "Running serial on Extra Case 1 5 times: 140000000."
									
TestingProject_SRL.exe 140000000
TestingProject_SRL.exe 140000000
TestingProject_SRL.exe 140000000
TestingProject_SRL.exe 140000000
TestingProject_SRL.exe 140000000

echo "Running serial on Extra Case 2 5 times: 70000000."
									
TestingProject_SRL.exe 70000000
TestingProject_SRL.exe 70000000
TestingProject_SRL.exe 70000000
TestingProject_SRL.exe 70000000
TestingProject_SRL.exe 70000000

echo "Running parallel programs for smallest case. "
echo "Running parallel on smallest case 5 times, for 2 cores."

mpiexec -n 2 TestingProject_PRLL.exe 720000000
mpiexec -n 2 TestingProject_PRLL.exe 720000000
mpiexec -n 2 TestingProject_PRLL.exe 720000000
mpiexec -n 2 TestingProject_PRLL.exe 720000000
mpiexec -n 2 TestingProject_PRLL.exe 720000000

echo "Running parallel on smallest case 5 times, for 4 cores."

mpiexec -n 4 TestingProject_PRLL.exe 720000000
mpiexec -n 4 TestingProject_PRLL.exe 720000000
mpiexec -n 4 TestingProject_PRLL.exe 720000000
mpiexec -n 4 TestingProject_PRLL.exe 720000000
mpiexec -n 4 TestingProject_PRLL.exe 720000000

echo "Running parallel on smallest case 5 times, for 8 cores."

mpiexec -n 8 TestingProject_PRLL.exe 720000000
mpiexec -n 8 TestingProject_PRLL.exe 720000000
mpiexec -n 8 TestingProject_PRLL.exe 720000000
mpiexec -n 8 TestingProject_PRLL.exe 720000000
mpiexec -n 8 TestingProject_PRLL.exe 720000000


echo "Running parallel programs for worst case. "
echo "Running parallel on worst case 5 times, for 2 cores."

mpiexec -n 2 TestingProject_PRLL.exe 1400000000
mpiexec -n 2 TestingProject_PRLL.exe 1400000000
mpiexec -n 2 TestingProject_PRLL.exe 1400000000
mpiexec -n 2 TestingProject_PRLL.exe 1400000000
mpiexec -n 2 TestingProject_PRLL.exe 1400000000

echo "Running parallel on worst case 5 times, for 4 cores."

mpiexec -n 4 TestingProject_PRLL.exe 1400000000
mpiexec -n 4 TestingProject_PRLL.exe 1400000000
mpiexec -n 4 TestingProject_PRLL.exe 1400000000
mpiexec -n 4 TestingProject_PRLL.exe 1400000000
mpiexec -n 4 TestingProject_PRLL.exe 1400000000

echo "Running parallel on worst case 5 times, for 8 cores."

mpiexec -n 8 TestingProject_PRLL.exe 1400000000
mpiexec -n 8 TestingProject_PRLL.exe 1400000000
mpiexec -n 8 TestingProject_PRLL.exe 1400000000
mpiexec -n 8 TestingProject_PRLL.exe 1400000000
mpiexec -n 8 TestingProject_PRLL.exe 1400000000

echo "Running parallel programs for Extra case 1: 140000000. "
echo "Running parallel on Extra case 1 5 times, for 2 cores."

mpiexec -n 2 TestingProject_PRLL.exe 140000000
mpiexec -n 2 TestingProject_PRLL.exe 140000000
mpiexec -n 2 TestingProject_PRLL.exe 140000000
mpiexec -n 2 TestingProject_PRLL.exe 140000000
mpiexec -n 2 TestingProject_PRLL.exe 140000000

echo "Running parallel on Extra case 1 5 times, for 4 cores."

mpiexec -n 4 TestingProject_PRLL.exe 140000000
mpiexec -n 4 TestingProject_PRLL.exe 140000000
mpiexec -n 4 TestingProject_PRLL.exe 140000000
mpiexec -n 4 TestingProject_PRLL.exe 140000000
mpiexec -n 4 TestingProject_PRLL.exe 140000000

echo "Running parallel on Extra case 1 5 times, for 8 cores."

mpiexec -n 8 TestingProject_PRLL.exe 140000000
mpiexec -n 8 TestingProject_PRLL.exe 140000000
mpiexec -n 8 TestingProject_PRLL.exe 140000000
mpiexec -n 8 TestingProject_PRLL.exe 140000000
mpiexec -n 8 TestingProject_PRLL.exe 140000000

echo "Running parallel programs for Extra case 2: 70000000. "
echo "Running parallel on Extra case 2 5 times, for 2 cores."

mpiexec -n 2 TestingProject_PRLL.exe 70000000
mpiexec -n 2 TestingProject_PRLL.exe 70000000
mpiexec -n 2 TestingProject_PRLL.exe 70000000
mpiexec -n 2 TestingProject_PRLL.exe 70000000
mpiexec -n 2 TestingProject_PRLL.exe 70000000

echo "Running parallel on Extra case 2 5 times, for 4 cores."

mpiexec -n 4 TestingProject_PRLL.exe 70000000
mpiexec -n 4 TestingProject_PRLL.exe 70000000
mpiexec -n 4 TestingProject_PRLL.exe 70000000
mpiexec -n 4 TestingProject_PRLL.exe 70000000
mpiexec -n 4 TestingProject_PRLL.exe 70000000

echo "Running parallel on Extra case 2 5 times, for 8 cores."

mpiexec -n 8 TestingProject_PRLL.exe 70000000
mpiexec -n 8 TestingProject_PRLL.exe 70000000
mpiexec -n 8 TestingProject_PRLL.exe 70000000
mpiexec -n 8 TestingProject_PRLL.exe 70000000
mpiexec -n 8 TestingProject_PRLL.exe 70000000