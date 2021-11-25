CREATE TABLE IF NOT EXISTS sales (
    id INTEGER PRIMARY KEY,
    symbol TEXT NOT NULL,
    name TEXT NOT NULL,
    user_id INTEGER NOT NULL,
    price REAL NOT NULL,
    shares INTEGER NOT NULL,
    created_at REAL NOT NULL
);
