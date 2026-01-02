# Security Policy

## Supported Versions

This library provides documentation and examples for DayZ modding. As a documentation repository, security concerns are primarily related to:

1. **Malicious code in examples**
2. **Vulnerable dependencies in tools**
3. **Harmful configurations that could compromise servers**

| Version | Supported          |
| ------- | ------------------ |
| Latest (main branch) | :white_check_mark: |
| Older commits | :x: |

## Reporting a Vulnerability

### What to Report

Please report:

- ✅ Malicious code in example scripts
- ✅ Security vulnerabilities in Python tools
- ✅ Configuration examples that could compromise server security
- ✅ Exploits or cheats documented in examples
- ✅ Injection vulnerabilities in validators/generators
- ✅ Unsafe practices recommended in documentation

### What Not to Report

Please do not report:

- ❌ DayZ game vulnerabilities (report to Bohemia Interactive)
- ❌ Third-party mod vulnerabilities (report to mod authors)
- ❌ Server hosting provider issues (report to providers)
- ❌ General DayZ gameplay exploits (not related to this library)

## How to Report

### For Security Issues

**DO NOT** create a public GitHub issue for security vulnerabilities.

Instead:

1. **Email**: Create a GitHub Security Advisory (preferred)
   - Go to: https://github.com/EVOLFATE/Dayz-Library/security/advisories/new
   
2. **Private Report**: Open an issue marked as private
   - Describe the vulnerability
   - Include steps to reproduce
   - Specify affected files/sections
   - Suggest fixes if possible

### Report Format

```
**Type**: [Code/Config/Documentation]
**Severity**: [Critical/High/Medium/Low]
**Component**: [File path or section]
**Description**: [Clear description of the issue]
**Impact**: [What could happen if exploited]
**Reproduction**: [Steps to verify the issue]
**Suggested Fix**: [Optional - your recommendation]
```

## Response Timeline

- **Acknowledgment**: Within 48 hours
- **Initial Assessment**: Within 5 days
- **Fix Timeline**: 
  - Critical: Within 7 days
  - High: Within 14 days
  - Medium: Within 30 days
  - Low: Next release cycle

## Security Best Practices

### For Users of This Library

1. **Validate All Code**
   - Review example scripts before using
   - Test in development environment first
   - Use validation tools before deployment

2. **Server Security**
   - Never use default passwords
   - Validate XML/JSON before deployment
   - Keep server software updated
   - Use BattlEye and anti-cheat tools

3. **Configuration Safety**
   - Backup before making changes
   - Test configurations on test servers
   - Review all parameter values
   - Monitor server logs after deployment

4. **Tool Usage**
   - Review Python scripts before running
   - Run tools in isolated environments
   - Validate tool outputs before use
   - Keep Python dependencies updated

### For Contributors

1. **Code Examples**
   - No malicious code or backdoors
   - No hardcoded credentials
   - Validate all user inputs
   - Use safe file operations
   - Comment security-critical sections

2. **Configuration Examples**
   - No vulnerable default settings
   - Document security implications
   - Warn about risks where applicable
   - Use strong passwords in examples (marked as CHANGE_ME)

3. **Tool Development**
   - Input validation on all tools
   - Safe file handling (no path traversal)
   - No execution of untrusted code
   - Dependency security scanning
   - Clear error messages (no sensitive info leaks)

## Security Tools in This Library

This library includes security-conscious tools:

1. **Configuration Validators** - Check for unsafe settings
2. **Link Checkers** - Prevent malicious link injection
3. **Code Templates** - Pre-vetted, secure starting points

## Known Security Considerations

### DayZ Server Administration

- **Admin Passwords**: Always change default passwords in serverDZ.cfg
- **RCon Access**: Restrict to trusted IPs only
- **BattlEye**: Always enable for public servers
- **Mod Signatures**: Verify mod sources before installation
- **Webhook URLs**: Keep Discord webhook URLs private

### Scripting Security

- **EnScript**: Server-side validation for all user inputs
- **RPC Calls**: Authenticate and authorize all remote procedures
- **File Operations**: Validate paths to prevent directory traversal
- **Database Access**: Use parameterized queries if using databases

## Disclosure Policy

Once a security issue is fixed:

1. Security advisory published on GitHub
2. Affected users notified via GitHub notifications
3. Fix details documented in commit messages
4. Credit given to reporter (if desired)

## Hall of Fame

We recognize security researchers who help improve this library:

*No reports yet - be the first!*

## Additional Resources

- [GitHub Security Best Practices](https://docs.github.com/en/code-security)
- [OWASP Top Ten](https://owasp.org/www-project-top-ten/)
- [Bohemia Interactive Security](https://www.bohemia.net/security)

## Questions?

For non-security questions about the library, please:
- Open a regular GitHub issue
- Check existing documentation
- Review the FAQ in README.md

---

**Last Updated**: January 2, 2026  
**Contact**: GitHub Security Advisories (preferred)  
**Response Time**: 48 hours acknowledgment
