#!/bin/bash

echo "Running tests..."
echo

# Run program and redirect input/output
./university < test/input.txt > test/actual_output.txt

# Check if program exited cleanly
if [ $? -eq 0 ]; then
    echo "✅ Program exited successfully"
else
    echo "❌ Program did not exit cleanly"
    exit 1
fi

# Normalize whitespace
filtered_output=$(tr -d '[:space:]' < test/actual_output.txt)
expected_output=$(tr -d '[:space:]' < test/expected_output.txt)

# Compare outputs
if [[ "$filtered_output" == "$expected_output" ]]; then
    echo "✅ Test passed"
else
    echo "❌ Test failed"
    echo "Expected: $expected_output"
    echo "Got     : $filtered_output"
    exit 1
fi
