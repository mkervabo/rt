#!/usr/bin/env node

const MAJOR = 0.5;
const MINOR = 0.2;
const Z = -3;

const MAX = 100;

for (let i = 0; i < MAX; i++) {
	const x = MAJOR * Math.cos(i / MAX * Math.PI * 2);
	const y = MAJOR * Math.sin(i / MAX * Math.PI * 2);

	console.log(`
		[[objects]]
			type = "SPHERE"
			material = "UV"
			position = { x = ${x.toFixed(2)}, y = ${y.toFixed(2)}, z = ${Z} }
			radius = ${MINOR}
	`);
}
