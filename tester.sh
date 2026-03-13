#!/bin/bash

ENGINE="./analyzer"
TEST_DIR="./tests"

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

pass=0
fail=0

run_test() {
	name=$1
	file=$2
	depth=$3
	expected=$4

	output=$($ENGINE "$TEST_DIR/$file" "$depth" 2>&1)

	if echo "$output" | grep -q "$expected"; then
		echo -e "${GREEN}PASS${NC} - $name"
		((pass++))
	else
		echo -e "${RED}FAIL${NC} - $name"
		echo "Expected: $expected"
		echo "Got:"
		echo "$output"
		((fail++))
	fi
}

echo "Running Chess Engine Tests"
echo "=========================="

# --------------------------
# Mate in N tests
# --------------------------

run_test "Mate in 1" mate1.chess 1 "White mates"
run_test "Mate in 2" mate2.chess 3 "White mates"
run_test "Mate in 3" mate3.chess 3 "White mates"
run_test "Mate in 4" mate4.chess 4 "White mates"

# --------------------------
# Already terminal positions
# --------------------------

run_test "Already checkmate" checkmate.chess 1 "king already in checkmate"
run_test "Already stalemate" stalemate.chess 1 "stalemate"

# --------------------------
# Invalid config tests
# --------------------------

run_test "Invalid piece config" invalid_piece.chess 1 "Error"
run_test "Invalid position" invalid_pos.chess 1 "Error"
run_test "Duplicate squares" duplicate_pos.chess 1 "Error"
run_test "Two white kings" two_white_kings.chess 1 "Error"
run_test "Pawn on first rank" pawn_first_rank.chess 1 "Error"

# --------------------------
# Parser errors
# --------------------------

run_test "Wrong extension" wrong_extension.txt 1 "Error"
run_test "Empty file" empty.chess 1 "Error"

# --------------------------
# Summary
# --------------------------

echo
echo "=========================="
echo "Passed: $pass"
echo "Failed: $fail"
echo "=========================="

if [ $fail -eq 0 ]; then
	echo -e "${GREEN}ALL TESTS PASSED${NC}"
else
	echo -e "${RED}SOME TESTS FAILED${NC}"
fi