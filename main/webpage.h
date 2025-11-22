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
    
    /* Button Colors */
    .btn-calib { background-color: #009688; } /* Teal */
    .btn-plot { background-color: #673AB7; }  /* Purple */
    
    .btn:active { transform: scale(0.98); opacity: 0.9; }
    a { text-decoration: none; }
  </style>
</head>
<body>

  <div class="card">
    <h2>Velocity Data</h2>
    <div class="chart-box">
      <canvas id="myChart"></canvas>
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
    const ctx = document.getElementById('myChart');
    
    // C++ injects either [] (empty) or [10, 20, 30] (data)
    const rawData = %DATA_ARRAY%; 

    // If data exists, make labels 1,2,3... If empty, no labels.
    const labels = rawData.length > 0 ? rawData.map((_, i) => i + 1) : [];

    new Chart(ctx, {
      type: 'line',
      data: {
        labels: labels,
        datasets: [{
          label: 'Velocity',
          data: rawData,
          borderColor: '#673AB7', // Purple line
          backgroundColor: 'rgba(103, 58, 183, 0.2)',
          fill: true,
          tension: 0.3
        }]
      },
      options: { 
        animation: false,
        maintainAspectRatio: false, 
        responsive: true,
        scales: {
          y: { beginAtZero: true, suggestedMax: 50 } // Keeps the grid looking nice even when empty
        }
      }
    });
  </script>

</body>
</html>
)rawliteral";

#endif