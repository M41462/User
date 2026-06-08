# AiChatBot

A CLI chatbot powered by Groq's Llama 3.3 70B model via the OpenAI-compatible API.

## How It Works

Loads a Groq API key from a `.env` file, creates an OpenAI-compatible client pointed at Groq's endpoint, and starts an interactive chat REPL. Maintains conversation history for context. Responses are printed character-by-character for a typewriter effect. Type `exit` or `quit` to end the session.

## Usage

```bash
pip install openai python-dotenv
# or: uv sync (if using uv)
```

Create a `.env` file with:
```
GROQ_API_KEY=your_key_here
```

Run:
```bash
python main.py
```
