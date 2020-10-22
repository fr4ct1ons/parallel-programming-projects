echo "Starting tests."

echo "Running serial on smallest case 5 times."
OETS_SRL.exe 51000
OETS_SRL.exe 51000
OETS_SRL.exe 51000
OETS_SRL.exe 51000
OETS_SRL.exe 51000

echo "Running serial on worst case 5 times."
									
OETS_SRL.exe 72000
OETS_SRL.exe 72000
OETS_SRL.exe 72000
OETS_SRL.exe 72000
OETS_SRL.exe 72000

echo "Running serial on Extra Case 1 5 times: 24000."
									
OETS_SRL.exe 24000
OETS_SRL.exe 24000
OETS_SRL.exe 24000
OETS_SRL.exe 24000
OETS_SRL.exe 24000

echo "Running serial on Extra Case 2 5 times: 30000."
									
OETS_SRL.exe 30000
OETS_SRL.exe 30000
OETS_SRL.exe 30000
OETS_SRL.exe 30000
OETS_SRL.exe 30000

echo "Running parallel programs for smallest case. "
echo "Running parallel on smallest case 5 times, for 2 cores."

mpiexec -n 2 OETS_PRLL.exe 51000
mpiexec -n 2 OETS_PRLL.exe 51000
mpiexec -n 2 OETS_PRLL.exe 51000
mpiexec -n 2 OETS_PRLL.exe 51000
mpiexec -n 2 OETS_PRLL.exe 51000

echo "Running parallel on smallest case 5 times, for 4 cores."

mpiexec -n 4 OETS_PRLL.exe 51000
mpiexec -n 4 OETS_PRLL.exe 51000
mpiexec -n 4 OETS_PRLL.exe 51000
mpiexec -n 4 OETS_PRLL.exe 51000
mpiexec -n 4 OETS_PRLL.exe 51000

echo "Running parallel on smallest case 5 times, for 8 cores."

mpiexec -n 8 OETS_PRLL.exe 51000
mpiexec -n 8 OETS_PRLL.exe 51000
mpiexec -n 8 OETS_PRLL.exe 51000
mpiexec -n 8 OETS_PRLL.exe 51000
mpiexec -n 8 OETS_PRLL.exe 51000


echo "Running parallel programs for worst case. "
echo "Running parallel on worst case 5 times, for 2 cores."

mpiexec -n 2 OETS_PRLL.exe 72000
mpiexec -n 2 OETS_PRLL.exe 72000
mpiexec -n 2 OETS_PRLL.exe 72000
mpiexec -n 2 OETS_PRLL.exe 72000
mpiexec -n 2 OETS_PRLL.exe 72000

echo "Running parallel on worst case 5 times, for 4 cores."

mpiexec -n 4 OETS_PRLL.exe 72000
mpiexec -n 4 OETS_PRLL.exe 72000
mpiexec -n 4 OETS_PRLL.exe 72000
mpiexec -n 4 OETS_PRLL.exe 72000
mpiexec -n 4 OETS_PRLL.exe 72000

echo "Running parallel on worst case 5 times, for 8 cores."

mpiexec -n 8 OETS_PRLL.exe 72000
mpiexec -n 8 OETS_PRLL.exe 72000
mpiexec -n 8 OETS_PRLL.exe 72000
mpiexec -n 8 OETS_PRLL.exe 72000
mpiexec -n 8 OETS_PRLL.exe 72000

echo "Running parallel programs for Extra case 1: 24000. "
echo "Running parallel on Extra case 1 5 times, for 2 cores."

mpiexec -n 2 OETS_PRLL.exe 24000
mpiexec -n 2 OETS_PRLL.exe 24000
mpiexec -n 2 OETS_PRLL.exe 24000
mpiexec -n 2 OETS_PRLL.exe 24000
mpiexec -n 2 OETS_PRLL.exe 24000

echo "Running parallel on Extra case 1 5 times, for 4 cores."

mpiexec -n 4 OETS_PRLL.exe 24000
mpiexec -n 4 OETS_PRLL.exe 24000
mpiexec -n 4 OETS_PRLL.exe 24000
mpiexec -n 4 OETS_PRLL.exe 24000
mpiexec -n 4 OETS_PRLL.exe 24000

echo "Running parallel on Extra case 1 5 times, for 8 cores."

mpiexec -n 8 OETS_PRLL.exe 24000
mpiexec -n 8 OETS_PRLL.exe 24000
mpiexec -n 8 OETS_PRLL.exe 24000
mpiexec -n 8 OETS_PRLL.exe 24000
mpiexec -n 8 OETS_PRLL.exe 24000

echo "Running parallel programs for Extra case 2: 30000. "
echo "Running parallel on Extra case 2 5 times, for 2 cores."

mpiexec -n 2 OETS_PRLL.exe 30000
mpiexec -n 2 OETS_PRLL.exe 30000
mpiexec -n 2 OETS_PRLL.exe 30000
mpiexec -n 2 OETS_PRLL.exe 30000
mpiexec -n 2 OETS_PRLL.exe 30000

echo "Running parallel on Extra case 2 5 times, for 4 cores."

mpiexec -n 4 OETS_PRLL.exe 30000
mpiexec -n 4 OETS_PRLL.exe 30000
mpiexec -n 4 OETS_PRLL.exe 30000
mpiexec -n 4 OETS_PRLL.exe 30000
mpiexec -n 4 OETS_PRLL.exe 30000

echo "Running parallel on Extra case 2 5 times, for 8 cores."

mpiexec -n 8 OETS_PRLL.exe 30000
mpiexec -n 8 OETS_PRLL.exe 30000
mpiexec -n 8 OETS_PRLL.exe 30000
mpiexec -n 8 OETS_PRLL.exe 30000
mpiexec -n 8 OETS_PRLL.exe 30000