'use client';

import { useEffect, useRef, useState } from 'react';

declare global {
  interface Window {
    PathfinderModule: any;
  }
}

export default function Home() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const [maze, setMaze] = useState<number[][]>([]);
  const [path, setPath] = useState<{ x: number; y: number }[]>([]);
  const [status, setStatus] = useState('Cliquez sur "Générer Labyrinthe" pour commencer.');
  const [module, setModule] = useState<any>(null);

  const width = 10;
  const height = 10;
  const cellSize = 50;
  const start = [0, 0];
  const end = [9, 9];

  useEffect(() => {
    // Load WebAssembly module by adding script tag
    const script = document.createElement('script');
    script.src = '/wasm/build/pathfinder.js';
    script.onload = () => {
      (window as any).PathfinderModule().then((mod: any) => {
        setModule(mod);
      });
    };
    document.head.appendChild(script);
  }, []);

  const drawMaze = () => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    const ctx = canvas.getContext('2d');
    if (!ctx) return;

    ctx.clearRect(0, 0, canvas.width, canvas.height);

    if (!maze || maze.length === 0) return;

    for (let y = 0; y < height; y++) {
      for (let x = 0; x < width; x++) {
        if (maze[y][x] === 1) {
          ctx.fillStyle = 'black';
          ctx.fillRect(x * cellSize, y * cellSize, cellSize, cellSize);
        } else {
          ctx.strokeRect(x * cellSize, y * cellSize, cellSize, cellSize);
        }
      }
    }

    // Draw start and end
    ctx.fillStyle = 'green';
    ctx.fillRect(start[0] * cellSize, start[1] * cellSize, cellSize, cellSize);
    ctx.fillStyle = 'red';
    ctx.fillRect(end[0] * cellSize, end[1] * cellSize, cellSize, cellSize);

    // Draw path
    if (path.length > 0) {
      ctx.strokeStyle = 'blue';
      ctx.lineWidth = 3;
      ctx.beginPath();
      ctx.moveTo(path[0].x * cellSize + cellSize / 2, path[0].y * cellSize + cellSize / 2);
      for (let i = 1; i < path.length; i++) {
        ctx.lineTo(path[i].x * cellSize + cellSize / 2, path[i].y * cellSize + cellSize / 2);
      }
      ctx.stroke();
    }
  };

  useEffect(() => {
    drawMaze();
  }, [maze, path]);

  const generateMaze = () => {
    const newMaze = Array.from({ length: height }, () => Array(width).fill(0));
    for (let y = 0; y < height; y++) {
      for (let x = 0; x < width; x++) {
        if ((x === start[0] && y === start[1]) || (x === end[0] && y === end[1])) continue;
        if (Math.random() < 0.3) newMaze[y][x] = 1;
      }
    }
    setMaze(newMaze);
    setPath([]);
    setStatus('Labyrinthe généré. Choisissez un algorithme.');
  };

  const runDijkstra = () => {
    if (!module) return;
    const walls: number[] = [];
    for (let y = 0; y < height; y++) {
      for (let x = 0; x < width; x++) {
        if (maze[y][x] === 1) {
          walls.push(x, y);
        }
      }
    }
    const result = module.dijkstraPath(width, height, walls, start[0], start[1], end[0], end[1]);
    setPath(result);
    setStatus(`Chemin trouvé avec Dijkstra : ${result.length} étapes.`);
  };

  const runBFS = () => {
    if (!module) return;
    const walls: number[] = [];
    for (let y = 0; y < height; y++) {
      for (let x = 0; x < width; x++) {
        if (maze[y][x] === 1) {
          walls.push(x, y);
        }
      }
    }
    const result = module.bfsPath(width, height, walls, start[0], start[1], end[0], end[1]);
    setPath(result);
    setStatus(`Chemin trouvé avec BFS : ${result.length} étapes.`);
  };

  return (
    <div className="min-h-screen bg-gray-100 flex flex-col items-center justify-center p-4">
      <h1 className="text-3xl font-bold mb-4 text-gray-800">Résolution de Labyrinthe avec Dijkstra et BFS</h1>
      <canvas
        ref={canvasRef}
        width={width * cellSize}
        height={height * cellSize}
        className="border border-gray-300 mb-4"
      />
      <div className="flex gap-4 mb-4">
        <button
          onClick={generateMaze}
          className="px-4 py-2 bg-blue-500 text-white rounded hover:bg-blue-600 transition"
        >
          Générer Labyrinthe
        </button>
        <button
          onClick={runDijkstra}
          disabled={!module}
          className="px-4 py-2 bg-green-500 text-white rounded hover:bg-green-600 disabled:bg-gray-400 transition"
        >
          Résoudre avec Dijkstra
        </button>
        <button
          onClick={runBFS}
          disabled={!module}
          className="px-4 py-2 bg-purple-500 text-white rounded hover:bg-purple-600 disabled:bg-gray-400 transition"
        >
          Résoudre avec BFS
        </button>
      </div>
      <p className="text-gray-600">{status}</p>
    </div>
  );
}
