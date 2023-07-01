const { spawn } = require('child_process');
const express = require('express');
const bodyParser = require("body-parser")

const app = express();
app.use(bodyParser.urlencoded({ extended: true }))

app.use(express.json());

// Serve the HTML file
app.get("/", (req, res) => {
  res.sendFile(__dirname + "/index.html")
});

// Handle the form submission
app.post('/calculateSum', (req, res) => {
  try {
    const { size, array } = req.body;
    const childProcess = spawn('./a.out', []);

    let result = '';

    childProcess.stdout.on('data', (data) => {
      result += data.toString();
    });

    childProcess.stderr.on('data', (data) => {
      console.error(`Child process error: ${data}`);
    });

    childProcess.on('close', (code) => {
      if (code === 0) {
        res.send(`
          <!DOCTYPE html>
          <html>
            <head>
              <title>Array Sum Calculator</title>
              <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css">
            </head>
            <body>
              <div class="container">
                <h1 class="text-center">Array Sum Calculator</h1>
                <div class="alert alert-success" role="alert">
                  The sum of the array is ${parseInt(result)}
                </div>
              </div>
            </body>
          </html>
        `);
      } else {
        res.status(500).json({ error: 'An error occurred while calculating the sum.' });
      }
    });

    // Pass the size and array as command line arguments to the C program
    childProcess.stdin.write(`${size}\n`);
    array.forEach((element) => {
      childProcess.stdin.write(`${element}\n`);
    });
    childProcess.stdin.end();
  } catch (error) {
    console.error(`Error occurred: ${error}`);
    res.status(500).json({ error: 'An error occurred while processing the request.' });
  }
});

app.listen(5000, () => {
  console.log('Server is running on port 5000');
});
