## The TC39 Process [Back](../tc39.md)

<table>
  <thead>
  <tr>
    <th>
    </th>
    <th>Stage
    </th>
    <th>Purpose
    </th>
    <th>Entrance Criteria
    </th>
    <th>Acceptance Signifies
    </th>
    <th>Spec Quality
    </th>
    <th>Post-Acceptance Changes Expected
    </th>
    <th>Implementation Types Expected*
    </th>
  </tr>
  </thead>
  <tbody>
  <tr>
    <td>0
    </td>
    <td>Strawperson
    </td>
    <td>Allow input into the specification
    </td>
    <td>None
    </td>
    <td>N/A
    </td>
    <td>N/A
    </td>
    <td>N/A
    </td>
    <td>N/A
    </td>
  </tr>
  <tr>
    <td>1
    </td>
    <td>Proposal
    </td>
    <td>
      <ul>
        <li>Make the case for the addition
        </li>
        <li>Describe the shape of a solution
        </li>
        <li>Identify potential challenges
        </li>
      </ul>
    </td>
    <td>
      <ul>
        <li>Identified “champion” who will advance the addition
        </li>
        <li>Prose outlining the problem or need and the general shape of a solution
        </li>
        <li>Illustrative examples of usage
        </li>
        <li>High-level API
        </li>
        <li>Discussion of key algorithms, abstractions and semantics
        </li>
        <li>Identification of potential “cross-cutting” concerns and implementation challenges/complexity
        </li>
      </ul>
    </td>
    <td>The committee expects to devote time to examining the problem space, solutions and cross-cutting concerns
    </td>
    <td>None
    </td>
    <td>Major
    </td>
    <td>Polyfills / demos
    </td>
  </tr>
  <tr>
    <td>2
    </td>
    <td>Draft
    </td>
    <td>Precisely describe the syntax and semantics using formal spec language
    </td>
    <td>
      <ul>
        <li>Above
        </li>
        <li>Initial spec text
        </li>
      </ul>
    </td>
    <td>The committee expects the feature to be developed and eventually included in the standard
    </td>
    <td>Draft: all <em>major</em> semantics, syntax and API are covered, but TODOs, placeholders and editorial issues are
      expected
    </td>
    <td>Incremental
    </td>
    <td>Experimental
    </td>
  </tr>
  <tr>
    <td>3
    </td>
    <td>Candidate
    </td>
    <td>Indicate that further refinement will require feedback from implementations and users
    </td>
    <td>
      <ul>
        <li>Above
        </li>
        <li>Complete spec text
        </li>
        <li>Designated reviewers have signed off on the current spec text
        </li>
        <li>All ECMAScript editors have signed off on the current spec text
        </li>
      </ul>
    </td>
    <td>The solution is complete and no further work is possible without implementation experience, significant usage and
      external feedback.
    </td>
    <td>Complete: all semantics, syntax and API are completed described
    </td>
    <td>Limited: only those deemed critical based on implementation experience
    </td>
    <td>Spec compliant
    </td>
  </tr>
  <tr>
    <td>4
    </td>
    <td>Finished
    </td>
    <td>Indicate that the addition is ready for inclusion in the formal ECMAScript standard
    </td>
    <td>
      <ul>
        <li>Above
        </li>
        <li><a href="https://github.com/tc39/test262">Test262</a> acceptance tests have been written for mainline usage
          scenarios, and merged
        </li>
        <li>Two compatible implementations which pass the acceptance tests
        </li>
        <li>Significant in-the-field experience with shipping implementations, such as that provided by two independent VMs
        </li>
        <li>A pull request has been sent to <a href="https://github.com/tc39/ecma262">tc39/ecma262</a> with the integrated spec
          text
        </li>
        <li>All ECMAScript editors have signed off on the pull request
        </li>
      </ul>
    </td>
    <td>The addition will be included in the soonest practical standard revision
    </td>
    <td>Final: All changes as a result of implementation experience are integrated
    </td>
    <td>None
    </td>
    <td>Shipping
    </td>
  </tr>
  </tbody>
</table>

\* This column does not indicate a requirement for advancement, but simply a general expectation.
