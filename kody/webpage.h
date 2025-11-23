#ifndef WEBPAGE_H
#define WEBPAGE_H

static const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>XIAO Dashboard</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  
  <style>
    body { font-family: -apple-system, sans-serif; text-align: center; margin: 0; padding: 20px; background-color: #f0f2f5; }
    .card { background: white; max-width: 600px; margin: 0 auto 20px auto; padding: 20px; border-radius: 20px; box-shadow: 0 4px 10px rgba(0,0,0,0.1); }
    .chart-box { position: relative; height: 300px; width: 100%; }
    .btn-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 15px; }
    .btn { border: none; color: white; padding: 20px 0; font-size: 16px; font-weight: bold; border-radius: 12px; cursor: pointer; width: 100%; touch-action: manipulation; }
    .btn-calib { background-color: #009688; } 
    .btn-plot { background-color: #673AB7; }
    .stats-box { font-size: 1.2rem; color: #333; text-align: left; line-height: 1.6; }
    .val { font-weight: bold; color: #673AB7; }
    a { text-decoration: none; }
  </style>
</head>
<body>

  <div class="card">
    <h2>Velocity vs Measurement</h2>
    <div class="chart-box"><canvas id="indexChart"></canvas></div>
  </div>

  <div class="card">
    <h2>Velocity vs Time</h2>
    <div class="chart-box"><canvas id="timeChart"></canvas></div>
  </div>

  <div class="card">
    <h2>Statistics</h2>
    <div class="stats-box">
      %STATS_HTML%
    </div>
  </div>

  <div class="card">
    <h2>Controls</h2>
    <div class="btn-grid">
        %BUTTON_1%
        %BUTTON_2%
    </div>
  </div>

  <script>
    // 1. Setup Data
    const rawData = %DATA_ARRAY%; // [10, 12, ...]
    const timeData = %XY_DATA%;   // [{x:0, y:10}, {x:50, y:12}...]

    // 2. Chart 1: Index
    new Chart(document.getElementById('indexChart'), {
      type: 'line',
      data: {
        labels: rawData.map((_, i) => i + 1),
        datasets: [{
          label: 'Velocity (cm/s)',
          data: rawData,
          borderColor: '#673AB7',
          backgroundColor: 'rgba(103, 58, 183, 0.2)',
          fill: true, tension: 0.3
        }]
      },
      options: { 
        animation: false, maintainAspectRatio: false, responsive: true,
        scales: {
          x: { title: { display: true, text: 'Measurement #' } },
          y: { title: { display: true, text: 'Velocity (cm/s)' }, beginAtZero: true }
        }
      }
    });

    // 3. Chart 2: Time
    new Chart(document.getElementById('timeChart'), {
      type: 'line',
      data: {
        datasets: [{
          label: 'Velocity over Time',
          data: timeData,
          borderColor: '#009688',
          backgroundColor: 'rgba(0, 150, 136, 0.2)',
          fill: true, tension: 0.3
        }]
      },
      options: { 
        animation: false, maintainAspectRatio: false, responsive: true,
        scales: {
          x: { type: 'linear', title: { display: true, text: 'Time (ms)' } },
          y: { title: { display: true, text: 'Velocity (cm/s)' }, beginAtZero: true }
        }
      }
    });
  </script>
</body>
</html>
)rawliteral";
#endif