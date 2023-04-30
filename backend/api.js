const express = require("express");
const { spawn } = require("child_process");
const fs = require("fs");
const path = require("path");
const app = express();

app.use(express.json()); // Add this middleware to parse JSON data

function safeDeleteFile(filePath) {
  if (fs.existsSync(filePath)) {
    fs.unlinkSync(filePath);
  }
}

// Define the route that will handle the API request
app.post("/process", (req, res) => {
  const time = Date.now();

  console.log("processing new request");

  if (!req.body) {
    return res.status(400).send("No JSON data provided");
  }

  // Save the received JSON
  const inputFile = `example/demo/in-${time}.json`;
  fs.writeFileSync(inputFile, JSON.stringify(req.body));

  const process = spawn("./build/main", [inputFile, time]);

  let output = "";
  process.stdout.on("data", (data) => {
    output += data;
  });

  // Handle errors from the C++ file
  process.stderr.on("data", (data) => {
    console.error(`Error: ${data}`);
  });

  // When the C++ file finishes processing, return the output file
  process.on("close", (code) => {
    if (code !== 0) {
      console.error(`Process exited with code ${code}`);
    }

    const outputFile = `example/demo/output-${time}.json`;
    console.log(`file written to: ${outputFile} \n`);
    res.sendFile(path.resolve(outputFile), () => {
      safeDeleteFile(inputFile);
      safeDeleteFile(outputFile);
    });
  });
});

// Start the server
app.listen(3000, () => {
  console.log("Server is running on port 3000");
});
