 # PCB
 PCB nie zostało wykonane — kupiona była zwykła płytka z otworami do lutowania THT. W razie posiadania czasu i finansów, wysoce zachęcane jest stworzenie własnego PCB na podstawie schematu, jednakże pamiętać należy o tym, aby nie wbudowywać lasera do płytki, tylko aby był podłączony na odległość od fotorezystora.
# Alternatywne układy
 Możliwym jest stworzenie układu w znacząco prostrzy sposób — rozdzielając układ zasilania lasera od ESP32. Wymagane byłoby umiejętne dobranie rezystora, oraz źródła zasilania (3–5V) do lasera. 
 W tym projekcie laser został połączony poprzez układ wzmacniający MOS ze względu na możliwość przyszłego rozwoju, tj. wyłączania lasera za pomocą przesyłanej strony.