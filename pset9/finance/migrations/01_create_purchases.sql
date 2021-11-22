CREATE TABLE IF NOT EXISTS purchases (
    purchase_id INTEGER PRIMARY KEY,
    symbol TEXT NOT NULL,
    name TEXT NOT NULL,
    user_id INTEGER NOT NULL,
    purchase_price REAL NOT NULL,
    shares INTEGER NOT NULL,
    created_at REAL NOT NULL
);
