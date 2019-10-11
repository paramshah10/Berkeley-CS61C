import argparse, os, re, subprocess, sys


filenamePattern = re.compile ("(.+)\.61c")
basePath = "tests"

def main (section, staffTests):
  # Next we want to get the list of all files for the tests we will be running
  files = os.listdir ("{}/{}/inputs".format (basePath, section))

  # Verify that the outputs folder exists
  with open ("/dev/null", "w") as f:
    subprocess.run (["mkdir", "-p", "{}/{}/outputs".format (basePath, section)], stdout=f, stderr=f)
 
  totalTests = 0
  testsPassed = 0
 
  # Now iterate through every file to produce results
  for f in files:
    # Select the base name of the test
    baseMatch = filenamePattern.match (f)
    if baseMatch:
      baseName = baseMatch.group (1)
      totalTests += 1
      # Run the compiler on the file and place the output in output
      destFile = "{}-output.S".format (baseName)
      with open ("{}/{}/outputs/{}".format (basePath, section, destFile), "w") as outputFile:
        res = subprocess.run (["./61ccc", "-c", "{}/{}/inputs/{}".format (basePath, section, f)], stdout=outputFile)
      if res.returncode:
        print ("Error in compiling the test.", file=sys.stderr)
      else:
        # Check if there is a .s/.S file to append to the output
        assemFile = "{}.S".format (baseName)
        if assemFile in files:
          with open ("{}/{}/outputs/{}".format (basePath, section, destFile), "a") as outputFile:
            subprocess.run (["cat", "{}/{}/inputs/{}".format (basePath, section, assemFile)], stdout=outputFile)
        assemFile = "{}.s".format (baseName)
        if assemFile in files:
          with open ("{}/{}/outputs/{}".format (basePath, section, destFile), "a") as outputFile:
            subprocess.run (["cat", "{}/{}/inputs/{}".format (basePath, section, assemFile)], stdout=outputFile)

        # Append the print library to the file
        with open ("{}/{}/outputs/{}".format (basePath, section, destFile), "a") as outputFile:
          subprocess.run (["cat", "cgen-lib/print.s"], stdout=outputFile)

        # Run the actual file through venus
        with open ("{}/{}/outputs/{}.out".format (basePath, section, baseName), "w") as outputFile:
          res = subprocess.run (["java", "-jar", "venus.jar", "{}/{}/outputs/{}".format (basePath, section, destFile)], stdout=outputFile)
          ret1 = res.returncode

        if staffTests:
          # Record and compare the result of the output
          res = subprocess.run (["diff", "{}/{}/outputs/{}.out".format (basePath, section, baseName), "{}/{}/expected/{}.out".format (basePath, section, baseName)])
          if res.returncode == 0:
            testsPassed += 1
          else:
            # Output whether/where it matched
            print ("Difference between output and expected output for {0}. Run:\n\n\ndiff {1}/{2}/outputs/{3}.out {1}/{2}/expected/{3}.out\n\n\n To view the differences.".format (f, basePath, section, baseName), file=sys.stderr)
  
  if staffTests:
    # Provide a hollistic output on the results for that part
    print ("{}: {}/{} Tests Passed".format (section, testsPassed, totalTests))

if __name__ == "__main__":
  parser = argparse.ArgumentParser (description="Runs all of the .")
  parser.add_argument ("--section", type=int, dest="section", help="Determines what stage of tests to run")
  stages = ["part1", "part2", "part3", "part4", "part5", "part6", "integration"]
  items = parser.parse_args ()
  if items.section == 0:
    main ("student-tests", False) 
  elif items.section < 1 or items.section > 7:
    print ("Invalid Argument")
    os.exit (1)
  else:
    main (stages[items.section - 1], True)
