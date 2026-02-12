// async function refresh() {
//   const r = await fetch("/status");
//   const j = await r.json();
//   document.getElementById("ip").textContent = j.ip;
//   document.getElementById("rssi").textContent = j.rssi;
// }
// setInterval(refresh, 1000);
// refresh();

document.addEventListener("DOMContentLoaded", () => {
  const hhEl = document.getElementById("hh");
  const mmEl = document.getElementById("mm");
  const saveBtn = document.getElementById("save");
  const resetBtn = document.getElementById("reset");
  const msgEl = document.getElementById("msg");

  function setMsg(text) {
    if (msgEl) msgEl.textContent = text;
  }

  function twoDigitsOnly(el) {
    el.value = el.value.replace(/\D/g, "").slice(0, 2);
  }

  hhEl.addEventListener("input", e => twoDigitsOnly(e.target));
  mmEl.addEventListener("input", e => twoDigitsOnly(e.target));

  saveBtn.addEventListener("click", async () => {
    // 1) Rohwerte abfangen
    const hhRaw = hhEl.value;
    const mmRaw = mmEl.value;

    // 2) Prüfen: genau 2 Stellen
    if (hhRaw.length !== 2 || mmRaw.length !== 2) {
      setMsg("Bitte HH und MM zweistellig eingeben.");
      return;
    }

    // 3) In Zahlen umwandeln
    const hh = Number(hhRaw);
    const mm = Number(mmRaw);

    if (!Number.isInteger(hh) || !Number.isInteger(mm)) {
      setMsg("Nur Zahlen erlaubt.");
      return;
    }
    if (hh < 0 || hh > 23 || mm < 0 || mm > 59) {
      setMsg("Ungültige Zeit.");
      return;
    }

    // 4) Senden (hier kannst du bewusst zweistellig senden)
    const body = new URLSearchParams({ hh: hhRaw, mm: mmRaw });

    try {
      const res = await fetch("/api/set", {
        method: "POST",
        headers: { "Content-Type": "application/x-www-form-urlencoded" },
        body,
      });

      const text = await res.text();
      setMsg(res.ok ? `Gespeichert: ${hhRaw}:${mmRaw}` : `Fehler: ${text}`);
    } catch {
      setMsg("Netzwerkfehler beim Speichern.");
    }
  });

  resetBtn.addEventListener("click", () => {
    hhEl.value = "";
    mmEl.value = "";
    setMsg("Zurückgesetzt.");
  });
});