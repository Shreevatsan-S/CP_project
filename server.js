const express = require('express');
const { spawn } = require('child_process');
const app = express();
const port = 3000;

app.use(express.static('public'));
app.use(express.json());

app.post('/calculate', (req, res) => {
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
			res.json({ result: parseInt(result) });
		} else {
			res.status(500).json({ error: 'An error occurred while calculating the amount of water trapped' });
		}
	});

	childProcess.stdin.write(`${size}\n`);
	array.forEach((element) => {
		childProcess.stdin.write(`${element}\n`);
	});
	childProcess.stdin.end();
});

app.listen(port, () => {
	console.log(`Server listening on port ${port}`);
});
