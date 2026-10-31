import random
import sys
try:
    import nltk
    from nltk.tokenize import sent_tokenize, word_tokenize
    # Ensure required nltk data is downloaded
    nltk.download('punkt', quiet=True)
    nltk.download('punkt_tab', quiet=True)
except ImportError:
    print("Please install nltk first using: pip install nltk")
    sys.exit()

# Sample study text (You can replace this or load your own text file!)
SAMPLE_TEXT = """
Python is a high-level, general-purpose programming language. Its design philosophy emphasizes code readability 
with the use of significant indentation. Python is dynamically typed and garbage-collected. It supports multiple 
programming paradigms, including structured, object-oriented, and functional programming. Artificial intelligence and 
machine learning rely heavily on Python because of its extensive libraries like TensorFlow, PyTorch, and Scikit-learn. 
Guido van Rossum began working on Python in the late 1980s as a successor to the ABC programming language. 
It was released in 1991. The name Python comes from the British comedy television show Monty Python's Flying Circus.
"""

def generate_questions(text):
    """Parses text into sentences and creates fill-in-the-blank questions."""
    sentences = sent_tokenize(text)
    questions = []
    
    for sentence in sentences:
        words = word_tokenize(sentence)
        # Filter for longer words that are likely nouns or key terms (length > 5)
        candidates = [w for w in words if w.isalpha() and len(w) > 5]
        
        if candidates:
            # Pick a random keyword to blank out
            secret_word = random.choice(candidates)
            # Create the blanked version (case-insensitive replacement)
            blanked_sentence = sentence.replace(secret_word, "______", 1)
            
            questions.append({
                "question": blanked_sentence,
                "answer": secret_word
            })
            
    return questions

def main():
    print("🧠 Welcome to your AI Flashcard & Quiz Generator!")
    print("=" * 50)
    
    # You could prompt the user for text or a file path here, 
    # but let's use our sample text for instant testing.
    print("Loading default study text about Python...")
    quiz_bank = generate_questions(SAMPLE_TEXT)
    
    if not quiz_bank:
        print("❌ Could not generate questions from the provided text.")
        return
    
    # Shuffle questions for a fresh quiz every time
    random.shuffle(quiz_bank)
    
    score = 0
    total = min(5, len(quiz_bank)) # Let's give a quick 5-question quiz
    
    print(f"\nStarting a quick quiz with {total} questions. Good luck!\n")
    
    for i in range(total):
        q = quiz_bank[i]
        print(f"Question {i+1}:")
        print(f"{q['question']}")
        
        user_answer = input("Your answer: ").strip()
        
        # Check answer (case-insensitive)
        if user_answer.lower() == q['answer'].lower():
            print("✅ Correct!\n")
            score += 1
        else:
            print(f"❌ Incorrect. The correct answer was: {q['answer']}\n")
            
    print("=" * 50)
    print(f"🎉 Quiz Finished! Your final score: {score}/{total}")

if __name__ == "__main__":
    main()